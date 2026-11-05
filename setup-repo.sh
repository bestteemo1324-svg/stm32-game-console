#!/usr/bin/env bash
# ============================================================
#  setup-repo.sh - LEADER chay DUY NHAT MOT LAN
#
#  Tao 2 commit dau theo Giai doan 0 cua quy trinh:
#    main    : cau truc thu muc + he thong build
#    develop : header hop dong + khung main.c
#  Sau do 3 Dev moi tao nhanh feature/* cua minh.
# ============================================================
set -e

if [ -d .git ]; then
    echo "Da co .git. Muon lam lai: rm -rf .git"
    exit 1
fi

git config --global user.name  >/dev/null 2>&1 || {
    echo 'Chay truoc: git config --global user.name  "Ho Ten"'; exit 1; }
git config --global user.email >/dev/null 2>&1 || {
    echo 'Chay truoc: git config --global user.email "email@cua.ban"'; exit 1; }

git init -q
git branch -M main

# ---------- main: khung + build ----------
git add .gitignore .clang-format Makefile STM32F103C8Tx_FLASH.ld \
        README.md HUONG-DAN-GIT.md setup-repo.sh
git commit -q -m "chore: khoi tao cau truc du an va he thong build

- Cau truc bsp/ hal/ drivers/ app/ middlewares/ theo quy trinh du an MCU
- Makefile cho arm-none-eabi-gcc, them muc tieu check va format
- Linker script STM32F103C8T6 64KB flash, 20KB RAM
- .clang-format va cppcheck lam quy uoc chung cho ca nhom"

# ---------- develop: hop dong giao tiep ----------
git checkout -q -b develop

git add bsp/ middlewares/FreeRTOSConfig.h
git commit -q -m "feat(bsp): so do chan, khoi tao xung nhip 72MHz va cau hinh kernel

- bsp.h: phan bo chan cho TFT, OLED, joystick, nut bam, buzzer, UART
- bsp.c: HSE 8MHz qua PLL x9 len 72MHz, flash 2 wait-state
- FreeRTOSConfig.h: heap 6KB, 5 muc uu tien, bat kiem tra tran stack"

git add app/inc/ hal/inc/ drivers/inc/
git commit -q -m "feat(core): dinh nghia hop dong giao tiep giua ba module

- app_types.h: trang thai game, su kien dau vao, thuc the, so lieu hieu nang
- app_ipc.h: hang doi, semaphore, mutex, event group dung chung
- app_cfg.h: do uu tien, stack, chu ky, nguong - thong nhat toan nhom
- hal/inc, drivers/inc: dac ta API cho tung Dev hien thuc"

git add app/src/app_ipc.c main.c hal/src/ drivers/src/ app/src/ tests/
git commit -q -m "feat(core): hien thuc IPC, khung main va khung unit test

- app_ipc.c: tao Queue/Semaphore/Mutex/EventGroup, khoa truy cap world_t
- main.c: trinh tu khoi tao, tao ba task, idle hook goi __WFI()
- hal/src, drivers/src, app/src: khung rong kem dac ta TODO cho tung Dev
- tests/: khung unit test chay tren PC cho logic game"

echo
echo "========================================================"
git --no-pager log --oneline --graph --all
echo "========================================================"
echo
echo " Viec tiep theo cua Leader:"
echo "   1. Tao repo rong tren GitHub (KHONG tich Add README)"
echo "   2. git remote add origin git@github.com:<user>/stm32-game-console.git"
echo "   3. git push -u origin main"
echo "   4. git push -u origin develop"
echo "   5. GitHub > Settings > Branches: bao ve main va develop"
echo "      (bat 'Require a pull request before merging')"
echo "   6. Gui link repo + HUONG-DAN-GIT.md cho ca nhom"
