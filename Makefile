# ============================================================
#  May choi game cam tay - STM32F103C8T6 + FreeRTOS
#  Toolchain: Arm GNU Toolchain (Ubuntu)
#    sudo apt install gcc-arm-none-eabi gdb-multiarch stlink-tools \
#                     cppcheck clang-format make
# ============================================================

TARGET  = game-console

PREFIX  = arm-none-eabi-
CC      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
SIZE    = $(PREFIX)size

CMSIS_DIR    = middlewares/CMSIS
FREERTOS_DIR = middlewares/FreeRTOS

# ---------- Ma nguon du an ----------
C_SOURCES = \
  main.c \
  bsp/src/bsp.c \
  hal/src/hal_gpio.c \
  hal/src/hal_spi.c \
  hal/src/hal_dma.c \
  hal/src/hal_i2c.c \
  hal/src/hal_adc.c \
  hal/src/hal_uart.c \
  hal/src/hal_pwm.c \
  drivers/src/st7735.c \
  drivers/src/ssd1306.c \
  drivers/src/joystick.c \
  app/src/app_ipc.c \
  app/src/task_render.c \
  app/src/task_game.c \
  app/src/task_hmi.c

# ---------- FreeRTOS ----------
C_SOURCES += \
  $(FREERTOS_DIR)/tasks.c \
  $(FREERTOS_DIR)/queue.c \
  $(FREERTOS_DIR)/list.c \
  $(FREERTOS_DIR)/timers.c \
  $(FREERTOS_DIR)/event_groups.c \
  $(FREERTOS_DIR)/portable/GCC/ARM_CM3/port.c \
  $(FREERTOS_DIR)/portable/MemMang/heap_4.c

C_SOURCES += $(CMSIS_DIR)/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

ASM_SOURCES = startup_stm32f103xb.s

C_INCLUDES = \
  -Ibsp/inc -Ihal/inc -Idrivers/inc -Iapp/inc -Imiddlewares \
  -I$(CMSIS_DIR)/Include \
  -I$(CMSIS_DIR)/Device/ST/STM32F1xx/Include \
  -I$(FREERTOS_DIR)/include \
  -I$(FREERTOS_DIR)/portable/GCC/ARM_CM3

CPU   = -mcpu=cortex-m3 -mthumb
DEFS  = -DSTM32F103xB
OPT   = -Og -g3
WARN  = -Wall -Wextra -Wshadow -Wundef -Wno-unused-parameter

CFLAGS = $(CPU) $(DEFS) $(C_INCLUDES) $(OPT) $(WARN) \
         -ffunction-sections -fdata-sections -std=gnu11

LDSCRIPT = STM32F103C8Tx_FLASH.ld
LDFLAGS  = $(CPU) -T$(LDSCRIPT) -specs=nano.specs -specs=nosys.specs \
           -Wl,-Map=build/$(TARGET).map,--cref -Wl,--gc-sections \
           -Wl,--print-memory-usage

OBJECTS  = $(addprefix build/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix build/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

all: build/$(TARGET).elf build/$(TARGET).hex build/$(TARGET).bin

build/%.o: %.c | build
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@

build/%.o: %.s | build
	$(CC) -c $(CPU) -x assembler-with-cpp $< -o $@

build/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

build/%.hex: build/%.elf
	$(OBJCOPY) -O ihex $< $@

build/%.bin: build/%.elf
	$(OBJCOPY) -O binary -S $< $@

build:
	mkdir -p build

# ---------- Nap firmware ----------
flash: build/$(TARGET).bin
	st-flash --reset write $< 0x8000000

# Blue Pill nhai (CKS32/APM32) khong nhan dien duoc thi dung lenh nay
flash-force: build/$(TARGET).bin
	st-flash --connect-under-reset --reset write $< 0x8000000

# ---------- Debug ----------
openocd:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg

gdb: build/$(TARGET).elf
	gdb-multiarch $< -ex "target extended-remote localhost:3333"

# ---------- Chat luong ma nguon ----------
# Chay TRUOC moi commit. PR khong sach thi khong merge.
SRC_OWN = main.c bsp/src drivers/src app/src hal/src

check:
	cppcheck --enable=warning,style,performance --std=c11 \
	         --inline-suppr --error-exitcode=1 \
	         -Ibsp/inc -Ihal/inc -Idrivers/inc -Iapp/inc \
	         $(SRC_OWN)

format:
	clang-format -i $$(find $(SRC_OWN) bsp/inc hal/inc drivers/inc app/inc \
	                   -name '*.c' -o -name '*.h' 2>/dev/null)

# ---------- Unit test tren PC (Dev 2) ----------
test:
	$(MAKE) -C tests run

clean:
	rm -rf build
	$(MAKE) -C tests clean 2>/dev/null || true

.PHONY: all clean flash flash-force openocd gdb check format test

-include $(wildcard build/*.d)
