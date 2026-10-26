#!/bin/bash

sudo ls /

primary=$'\e[38;2;239;133;40m'
secondary=$'\e[38;2;40;146;239m'
text=$'\e[0m'
time = $(date +%F-%H%M)

echo -e "${primary}) WARNING: THIS SCRIPT IS UNTESTED AND UNFINISHED. PLEASE PRESS CTRL+C TO QUIT IF YOU DON'T WANT TO PROCEED${text}"
sleep 5

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
echo -e "${primary}) Backing up /etc/regreet /etc/regreet-${time} (REQUIRES SUDO, OPTIONAL)${text}"
sudo cp -rv /etc/regreet /etc/regreet-backup-chlebqowy-${time}
echo -e "${primary}) Installing Iosevka ${text}"
sudo cp -rv ./Iosevka /etc/fonts/Iosevka
echo -e "${primary}) Installing local.conf${text}"
sudo cp -rv ./local.conf /etc/fonts/local.conf
echo -e "${primary}) Refreshing font cache${text}"
sudo fc-cache -fv
echo -e "${primary}) Installing regreet config${text}"
sudo cp -rv ./etc/regreet /etc/regreet
echo -e "${primary}) Installing cross-platform configs${text}"
cp -rv ./cross-platform/* ~/.config/
echo -e "${primary}) Installing display wayland configs${text}"
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
cd src
make
make install-global
echo -e "\x1b[32m✓ Finished${text}"
echo -e "${secondary} Please make sure all dependencies from README.md are installed${text}"
echo -e "${secondary} Please reboot after installing them${text}"
