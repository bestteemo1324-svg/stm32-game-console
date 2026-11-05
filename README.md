# Hệ thống đồ họa thời gian thực trên STM32 — máy chơi game cầm tay

Bài tập lớn môn Hệ thống Nhúng. STM32F103C8T6 + FreeRTOS, ba module cho ba người.

---

## 1. Kiến trúc

```
 joystick ──ADC──┐                                    ┌──SPI+DMA──> TFT ST7735
 nút bấm ──EXTI──┤                                    │
                 v                                    │
         [TASK_HMI] ──queue──> [TASK_GAME] ──sem──> [TASK_RENDER]
          prio 3               prio 2                prio 1    │
          50 Hz                50 Hz                 sự kiện    └──I2C──> OLED
             │                    ^                                       (số liệu)
             └──PWM──> buzzer     │
                            software timer
                            (sinh đợt gà)
```

Ba task **không gọi hàm của nhau**. Mọi trao đổi đi qua đối tượng khai báo trong `app/inc/app_ipc.h`. Nhờ đó mỗi người code và test độc lập trước khi ghép.

---

## 2. Cấu trúc thư mục

```
stm32-game-console/
├── bsp/            Sơ đồ chân, khởi tạo xung nhịp          [Leader]
├── hal/            Driver ngoại vi bare-metal              [chia 3 người]
├── drivers/        ST7735, SSD1306, joystick               [chia 3 người]
├── app/            Ba task FreeRTOS + IPC                  [chia 3 người]
├── middlewares/    FreeRTOSConfig.h + kernel (tự tải)
├── tests/          Unit test chạy trên PC                  [Dev 2]
├── main.c          Khởi tạo và tạo task                    [Leader]
└── Makefile
```

---

## 3. Phân công

| Dev | Module | Task sở hữu | Driver phụ trách |
|---|---|---|---|
| 1 | Hiển thị | `TASK_RENDER` | SPI, DMA, ST7735, SSD1306 |
| 2 | Game engine | `TASK_GAME` | I2C, ADC, unit test |
| 3 | Giao diện người dùng | `TASK_HMI` | GPIO, UART, Timer PWM, joystick |
| Leader | — | — | `main.c`, `bsp/`, `app_*.h`, `app_ipc.c`, `FreeRTOSConfig.h` |

**Không ai được commit trực tiếp** vào `main.c`, `app_cfg.h`, `app_types.h`, `app_ipc.h`, `bsp.h`, `FreeRTOSConfig.h`. Muốn đổi thì đề xuất trong PR, Leader sửa.

Quy trình Git chi tiết: xem `HUONG-DAN-GIT.md`.

---

## 4. Ba ràng buộc kỹ thuật — nội dung chính của báo cáo

### Bộ nhớ: 40 KB framebuffer trên 20 KB RAM

Một khung TFT đầy đủ cần `128 × 160 × 2 = 40.960` byte. Blue Pill chỉ có 20.480 byte RAM — **không nhét vừa**.

Giải pháp: chia 20 dải, mỗi dải `128 × 8` pixel = 2.048 byte. Dùng **hai đệm**: DMA đẩy đệm A trong khi CPU vẽ đệm B, rồi đổi vai.

| Thành phần | RAM |
|---|---|
| Hai đệm dải TFT | 4,1 KB |
| Heap FreeRTOS | 6,1 KB |
| Framebuffer OLED | 1,0 KB |
| `world_t` | 0,6 KB |
| Stack chính | 1,0 KB |
| **Tổng** | **~12,8 / 20 KB** |

Còn dư ~7 KB. Khai báo bừa một mảng lớn là tràn ngay — theo dõi `xPortGetFreeHeapSize()` từ tuần đầu.

### Thời gian: 33 ms mỗi khung

Ở 30 FPS mỗi khung có 33,3 ms. Truyền toàn bộ khung qua SPI 18 MHz mất **18,2 ms**, CPU vẽ và tính khoảng 8 ms. Không có DMA thì cộng dồn thành 26 ms và CPU bận 100%. Có DMA thì hai phần chồng lên nhau.

Số liệu để báo cáo: đo FPS **trước và sau** khi bật DMA.

### Điện năng

Ở 30 FPS, DMA gánh phần truyền nên CPU rảnh khoảng 70%. `__WFI()` trong `vApplicationIdleHook()` cho CPU ngủ đến ngắt kế tiếp. Kẹp đồng hồ đo dòng, so sánh khi bật và tắt `USE_LOW_POWER_IDLE` trong `app_cfg.h`.

---

## 5. Sơ đồ nối dây

| Chân | Chức năng | Ghi chú |
|---|---|---|
| PA0, PA1 | Joystick X, Y | ADC1_IN0, IN1 |
| PA2–PA5, PA7 | TFT: RST, DC, CS, SCK, MOSI | SPI1, 18 MHz |
| PA9, PA10 | UART1 TX, RX | 115200-8N1, nối USB-TTL |
| PB0 | Buzzer **passive** | TIM3_CH3, đệm qua transistor NPN |
| PB6, PB7 | OLED SCL, SDA | I2C1, địa chỉ 0x3C |
| PB12, PB13 | Nút BẮN, nút START/PAUSE | Pull-up nội, EXTI |
| PC13 | LED onboard | Nhịp tim, tích cực mức thấp |

Kênh DMA1: kênh 1 cho ADC1, kênh 3 cho SPI1_TX.

---

## 6. Build và nạp

Chạy một lần sau khi clone:

```bash
./get-libs.sh
```

Script tải CMSIS Core (ARM), CMSIS Device F1 (ST), FreeRTOS và file startup, rồi tự kiểm tra đủ chưa.

```bash
sudo apt install gcc-arm-none-eabi gdb-multiarch stlink-tools \
                 cppcheck clang-format make

make              # biên dịch
make flash        # nạp bằng ST-Link
make flash-force  # Blue Pill nhái (CKS32/APM32) không nhận diện được
make check        # cppcheck — bắt buộc trước commit
make format       # clang-format — bắt buộc trước commit
make test         # unit test logic game, chạy trên PC
```

> VirtualBox: nhớ bật USB passthrough cho ST-Link (cài Extension Pack, thêm USB filter), và thêm udev rules trong Ubuntu để không phải chạy `sudo`.

---

## 7. Kế hoạch 5 tuần

| Tuần | Nội dung | Mốc kiểm tra |
|---|---|---|
| 1 | Tải thư viện, build sạch. Bắt đầu HAL. Dev 2 viết unit test trước. | Cả ba `make` chạy được |
| 2 | Xong HAL, merge vào `develop`. | TFT sáng, hiện được hình tĩnh |
| 3 | Ba task chạy song song, game chơi được dù còn xấu. | Bắn được gà, có điểm |
| 4 | Đổi sang DMA hai đệm. Đo FPS trước/sau. Âm thanh, HUD, `__WFI()`. | FPS ≥ 30 ổn định |
| 5 | Đo tài nguyên và dòng điện, hoàn thiện báo cáo, tập demo. | Báo cáo xong |

---

## 8. Tiêu chí nghiệm thu

- [ ] FPS ≥ 30 ổn định khi có đủ 12 gà trên màn hình
- [ ] Đo được chênh lệch FPS trước và sau khi bật DMA
- [ ] Đo được chênh lệch dòng điện khi bật và tắt `__WFI()`
- [ ] Stack high water mark mỗi task còn dư ≥ 50 words
- [ ] `make check` sạch, không cảnh báo
- [ ] `make test` chạy hết, không ca nào trượt
- [ ] Rút dây OLED giữa lúc chơi — game vẫn chạy bình thường
- [ ] Cố tình treo một task — watchdog reset board sau 2 giây

---

## 9. Bộ câu hỏi tự kiểm tra

Cuối mỗi tuần mỗi người tự trả lời phần của mình. Đây đúng kiểu câu thầy sẽ hỏi lúc bảo vệ.

**Dev 1** — Tại sao không để cả framebuffer trong RAM? Tại sao chọn dải 8 dòng? Trong lúc DMA chạy thì CPU làm gì? Bỏ DMA thì FPS còn bao nhiêu, vì sao?

**Dev 2** — Tại sao tọa độ dùng Q12.4 thay vì số nguyên pixel? Mỗi frame kiểm tra bao nhiêu phép va chạm? Tại sao `world_t` cần mutex, bỏ mutex thì hỏng kiểu gì?

**Dev 3** — Joystick trả về bao nhiêu khi thả tay, vì sao cần vùng chết? Nút bấm xử lý trong ISR hay trong task, vì sao? Tại sao trong ISR chỉ được gọi hàm có đuôi `FromISR`?
