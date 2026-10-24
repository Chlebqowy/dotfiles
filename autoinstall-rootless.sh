#!/bin/bash

primary=$'\e[38;2;117;255;152m'
secondary=$'\e[38;2;79;218;88m'
text=$'\e[38;2;251;254;252m'
# todo update colors, use default for text
time = $(date +%F-%H%M)

mkdir -pv ~/.config
mkdir -pv ~/.fonts #most likely exist but I have to make sure
echo -e "${primary}) Backing up ~/.config to ~/.config-backup-chlebqowy-${time}${text}"
cp -rv ~/.config ~/.config-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.fonts to ~/.fonts-backup-chlebqowy-${time}${text}"
cp -rv ~/.fonts ~/.fonts-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.bashrc to ~/.bashrc-backup-chlebqowy-${time} ${text}"
cp -rv ~/.bashrc ~/.bashrc-backup-chlebqowy-${time}
echo -e "${primary}) Installing Iosevka${text}"
cp -rv ./Iosevka ~/.fonts/Iosevka
echo -e "${primary}) Installing local.conf${text}"
cp -rv ./local.conf ~/.fonts/local.conf
echo -e "${primary}) Refreshing font cache${text}"
fc-cache -fv
echo -e "${primary}) Installing cross-platform configs${text}"
cp -rv ./cross-platform/* ~/.config/
echo -e "${primary}) Installing wayland configs${text}"
cp -rv ./wayland/* ~/.config
echo -e "${primary}) Installing shell scripts${text}"
mkdir -pv ~/scripts
cp -vn ./scripts/* ~/scripts/
echo -e "${primary}) Installing wallpapers${text}"
mkdir -pv ~/Pictures
mkdir -pv ~/Pictures/Important
cp -vn ./pictures/* ~/Pictures/Important
echo -e "${primary}) Installing .bashrc${text}"
cat ./.bashrc
cat ./.bashrc >> ~/.bashrc
cat ~/.bashrc
echo -e "${primary}) Building c++ and c scripts${text}"
sleep 1
g++ src/chlebqowy-workspace-bar.cpp -o bin/chlebqowy-workspace-bar
g++ src/chlebqowy-update-num.cpp -o bin/chlebqowy-update-num
g++ src/chlebqowy-gpu-usage.cpp -o bin/chlebqowy-gpu-usage
cp -rv bin/chlebqowy-gpu-usage ~/.local/bin/chlebqowy-gpu-usage
cp -rv bin/chlebqowy-update-num ~/.local/bin/chlebqowy-update-num
cp -rv bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
echo -e "\x1b[32m✓ Finished${text}"
echo -e "${secondary} Please make sure all dependencies from README.md are installed${text}"
echo -e "${secondary} Please reboot after installing them${text}"
