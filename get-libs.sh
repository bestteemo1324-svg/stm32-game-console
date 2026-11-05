#!/usr/bin/env bash
# Tai CMSIS + FreeRTOS + startup. Moi nguoi chay mot lan sau khi clone.
set -e
TMP=$(mktemp -d); trap 'rm -rf "$TMP"' EXIT

echo ">> [1/3] CMSIS Core (ARM)..."
git clone -q --depth 1 --filter=blob:none --sparse \
    https://github.com/STMicroelectronics/STM32CubeF1.git "$TMP/cube"
git -C "$TMP/cube" sparse-checkout set Drivers/CMSIS >/dev/null
rm -rf middlewares/CMSIS
cp -r "$TMP/cube/Drivers/CMSIS" middlewares/CMSIS

echo ">> [2/3] CMSIS Device F1 (ST) + startup..."
git clone -q --depth 1 \
    https://github.com/STMicroelectronics/cmsis_device_f1.git "$TMP/devf1"
mkdir -p middlewares/CMSIS/Device/ST/STM32F1xx
cp -r "$TMP/devf1/Include" middlewares/CMSIS/Device/ST/STM32F1xx/
cp -r "$TMP/devf1/Source"  middlewares/CMSIS/Device/ST/STM32F1xx/
cp "$TMP/devf1/Source/Templates/gcc/startup_stm32f103xb.s" .

echo ">> [3/3] FreeRTOS Kernel..."
git clone -q --depth 1 --branch V10.6.2 \
    https://github.com/FreeRTOS/FreeRTOS-Kernel.git "$TMP/rtos"
rm -rf middlewares/FreeRTOS
mkdir -p middlewares/FreeRTOS/portable/GCC middlewares/FreeRTOS/portable/MemMang
cp "$TMP/rtos"/*.c middlewares/FreeRTOS/
cp -r "$TMP/rtos/include" middlewares/FreeRTOS/
cp -r "$TMP/rtos/portable/GCC/ARM_CM3" middlewares/FreeRTOS/portable/GCC/
cp "$TMP/rtos/portable/MemMang/heap_4.c" middlewares/FreeRTOS/portable/MemMang/

echo
for f in middlewares/CMSIS/Include/core_cm3.h \
         middlewares/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h \
         middlewares/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c \
         middlewares/FreeRTOS/tasks.c \
         middlewares/FreeRTOS/portable/GCC/ARM_CM3/port.c \
         startup_stm32f103xb.s ; do
    [ -f "$f" ] && echo "   [OK]     $f" || echo "   [THIEU]  $f"
done
echo
echo "Xong. Chay tiep:  make"
