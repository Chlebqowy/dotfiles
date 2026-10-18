#!/bin/bash

sudo ls /

primary=$'\e[38;2;117;255;152m'
secondary=$'\e[38;2;79;218;88m'
text=$'\e[38;2;251;254;252m'

time = $(date +%F-%H%M)

mkdir -pv ~/.config
mkdir -pv ~/.fonts #most likely exist but I have to make sure
echo -e "${primary}) Backing up ~/.config to ~/.config-backup-chlebqowy-${time}${text}"
cp -rv ~/.config ~/.config-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.fonts to ~/.fonts-backup-chlebqowy-${time}${text}"
cp -rv ~/.fonts ~/.fonts-backup-chlebqowy-${time}
echo -e "${primary}) Backing up /etc/fonts to /etc/fonts-backup-chlebqowy-${time} (REQUIRES SUDO, OPTIONAL)${text}"
sudo cp -rv /etc/fonts /etc/fonts-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.bashrc to ~/.bashrc-backup-chlebqowy-${time} (REQUIRES SUDO, OPTIONAL)${text}"
sudo cp -rv ~/.bashrc ~/.bashrc-backup-chlebqowy-${time}
echo -e "${primary}) Installing departure mono${text}"
sudo cp -rv ./departure_mono_nerd.otf /etc/fonts/departure_mono_nerd.otf
echo -e "${primary}) Installing local.conf${text}"
sudo cp -rv ./local.conf /etc/fonts/local.conf
echo -e "${primary}) Refreshing font cache${text}"
sudo fc-cache -fv
echo -e "${primary}) Installing cross-platform configs${text}"
cp -rv ./cross-platform/* ~/.config/
echo -e "${primary}) Installing display server_specific configs${text}"
sudo cp -rv ./xorg/* ~/.config
sudo cp -rv ./wayland/* ~/.config
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
g++ src/chlebqowy-workspace-bar.cpp -o bin/chlebqowy-workspace-bar
g++ src/chlebqowy-update-num.cpp -o bin/chlebqowy-update-num
g++ src/chlebqowy-gpu-usage.cpp -o bin/chlebqowy-gpu-usage
sudo cp -rv bin/chlebqowy-gpu-usage /usr/bin/chlebqowy-gpu-usage
sudo cp -rv bin/chlebqowy-update-num /usr/bin/chlebqowy-update-num
sudo cp -rv bin/chlebqowy-workspace-bar /usr/bin/chlebqowy-workspace-bar
echo -e "${primary}) Installing dmenu${text}"
cd src/dmenu
make
cd ../..
sudo mv -v ./bin/dmenu /usr/bin/dmenu
sudo mv -v ./bin/dmenu_run /usr/bin/dmenu_run
sudo mv -v ./bin/dmenu_path /usr/bin/dmenu_path
echo -e "\x1b[32m✓ Finished${text}"
echo -e "${secondary} Please make sure all dependencies from README.md are installed${text}"
echo -e "${secondary} Please reboot after installing them${text}"
