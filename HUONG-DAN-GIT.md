# Hướng dẫn Git cho nhóm — đọc hết trước khi gõ dòng lệnh đầu tiên

Repo chia **hai vòng nhánh** đúng như thầy vẽ trên bảng: vòng một viết driver HAL chia theo ngoại vi, vòng hai viết task chia theo module.

Mục tiêu không chỉ là lưu code, mà để **lịch sử Git chứng minh được ba người cùng làm**. Một người push tất cả là hỏng phần đó.

---

## 0. Ai làm gì

| Người | Vòng 1 — HAL | Vòng 2 — Task |
|---|---|---|
| **Dev 1** | `feature/hal-spi`, `feature/hal-dma` | `feature/task-render` |
| **Dev 2** | `feature/hal-i2c`, `feature/hal-adc` | `feature/task-game` |
| **Dev 3** | `feature/hal-gpio`, `feature/hal-uart`, `feature/hal-timer-pwm` | `feature/task-hmi` |

---

## 1. Leader làm trước — một lần duy nhất

```bash
git config --global user.name  "Họ Tên Leader"
git config --global user.email "email@cua.ban"

cd stm32-game-console
./setup-repo.sh
```

Script tạo 4 commit: khung build trên `main`, rồi BSP + header hợp đồng + khung IPC trên `develop`. Sau đó làm theo 6 bước script in ra.

---

## 2. Tải thư viện ngoài — mỗi người tự làm

Ba thứ này **không commit vào repo** (đã nằm trong `.gitignore`), mỗi người tự tải về máy mình:

```bash
# CMSIS + device header, lấy từ STM32CubeF1
#   -> middlewares/CMSIS/
# FreeRTOS kernel v10.x
#   -> middlewares/FreeRTOS/
# File startup
#   -> startup_stm32f103xb.s  (ở thư mục gốc)
```

Xong thì `make` phải chạy sạch. Nếu lỗi, xử lý ngay — đừng để sang tuần sau.

---

## 3. Vòng 1 — viết driver HAL

Lấy Dev 1 làm ví dụ.

```bash
git clone <url-repo> && cd stm32-game-console
git config user.name  "Họ Tên Dev 1"
git config user.email "email@cua.ban"

git checkout develop && git pull origin develop
git checkout -b feature/hal-spi
```

Mở `hal/inc/hal_spi.h` đọc đặc tả, mở `hal/src/hal_spi.c` đọc phần `TODO` — trong đó có các bước làm và cái bẫy hay gặp. Viết, nạp lên kit, test theo đúng cách ghi trong TODO.

```bash
make format && make check     # bắt buộc, trước mọi commit
git add hal/src/hal_spi.c
git commit -m "feat(hal): them driver SPI1 che do chi gui 18MHz

- Cau hinh master mode 0, MSB first, BR = APB2/4
- Cho co BSY ha truoc khi nha CS, tranh mat byte cuoi
- Da do bang logic analyzer: xung SCK dung 18MHz, du lieu khop"

git push -u origin feature/hal-spi
```

Commit **nhiều lần theo tiến độ thật**, đừng dồn thành một commit khổng lồ cuối tuần. Commit message ghi rõ **đã kiểm chứng thế nào** — đó là thứ phân biệt người làm thật với người chép.

Mở Pull Request vào `develop`, gắn hai người còn lại làm reviewer.

---

## 4. Review PR — bắt buộc, không duyệt lấy lệ

- [ ] Đúng API trong header, không tự đổi chữ ký hàm
- [ ] Mọi vòng chờ cờ phần cứng đều có timeout
- [ ] ISR chỉ gọi hàm có đuôi `...FromISR()`
- [ ] Không `HAL_Delay()` hay vòng lặp chờ trong task — chỉ `vTaskDelay`/`vTaskDelayUntil`
- [ ] Không lấy mutex với `portMAX_DELAY`
- [ ] `make check` sạch, `make format` đã chạy
- [ ] Không có `build/`, file IDE trong diff

Để lại comment cụ thể trên dòng code. PR chỉ có "LGTM" không tính là có review.

---

## 5. Vòng 2 — viết task

Sau khi cả ba HAL đã vào `develop`:

```bash
git checkout develop && git pull origin develop
git checkout -b feature/task-render
```

Đọc khung vòng lặp trong file `.c` của mình — có sẵn sườn và các bẫy. Test độc lập: tạm thời sửa `main.c` **bản local của bạn** để chỉ tạo mỗi task của mình, chạy với dữ liệu giả. Xong thì `git checkout main.c` trả lại — **không commit `main.c`**.

Dev 2 có lợi thế: `make test` chạy trên PC, không cần kit, nên làm được ngay từ tuần 1.

---

## 6. Đồng bộ khi có xung đột

```bash
git fetch origin
git rebase origin/develop
# conflict: sửa file, git add <file>, git rebase --continue
git push --force-with-lease origin feature/task-render
```

Dùng `--force-with-lease`, **không dùng `--force`**. Nó từ chối đẩy nếu có người khác vừa push lên nhánh đó.

---

## 7. Tích hợp và phát hành

```bash
git checkout develop && git pull origin develop
git checkout -b integration/system-v1
```

Cả nhóm ngồi cùng nhau ghép, chạy trên kit, đo FPS, đo heap và stack, đo dòng điện. Xong:

```bash
git checkout develop && git merge --no-ff integration/system-v1
git checkout main && git merge --no-ff develop
git tag -a v1.0.0 -m "Release v1.0.0"
git push origin main develop --tags
```

Luôn `--no-ff` để `git log --graph` giữ lại hình dạng nhánh — lúc bảo vệ, đó là bằng chứng ba luồng làm việc song song.

---

## 8. Quy ước commit message

```
feat(hal): them driver SPI1 che do chi gui
fix(render): sua mat dai cuoi khi DMA chua xong
refactor(game): tach ham va cham ra khoi vong lap chinh
test(game): them 6 ca kiem thu cho game_aabb_overlap
docs(readme): bo sung bang do tai nguyen
```

Phạm vi dùng: `hal`, `bsp`, `render`, `game`, `hmi`, `core`, `readme`.

---

## 9. Tuyệt đối không làm

- Commit thẳng vào `main` hoặc `develop`
- Sửa `main.c`, `app_cfg.h`, `app_types.h`, `app_ipc.h`, `bsp.h`, `FreeRTOSConfig.h` mà không qua Leader
- Commit `build/`, `middlewares/CMSIS/`, `middlewares/FreeRTOS/`, file IDE
- `git push --force` lên nhánh người khác đang dùng
- Commit code chưa từng nạp lên kit
