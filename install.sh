#!/bin/bash

primary=$'\e[38;2;117;255;152m'
secondary=$'\e[38;2;79;218;88m'
text=$'\e[38;2;251;254;252m'
# todo update colors, use default for text
time = $(date +%F-%H%M)

mkdir -pv ~/.config
mkdir -pv ~/.fonts #most likely exist but I have to make sure
echo -e "${primary}) Backing up ~/.config to ~/.config-backup-chlebqowy-${time}${text}"
sleep 1
cp -rv ~/.config ~/.config-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.fonts to ~/.fonts-backup-chlebqowy-${time}${text}"
sleep 1
cp -rv ~/.fonts ~/.fonts-backup-chlebqowy-${time}
echo -e "${primary}) Backing up /etc/fonts to /etc/fonts-backup-chlebqowy-${time} (REQUIRES SUDO, OPTIONAL)${text}"
sleep 1
sudo cp -rv /etc/fonts /etc/fonts-backup-chlebqowy-${time}
echo -e "${primary}) Backing up ~/.bashrc to ~/.bashrc-backup-chlebqowy-${time} (REQUIRES SUDO, OPTIONAL)${text}"
sleep 1
sudo cp -rv ~/.bashrc ~/.bashrc-backup-chlebqowy-${time}
echo -e "${primary}) Installing Iosevka${text}"
sleep 1
read -rp "${secondary}Install globally or locally? [g/l]: ${text}" answer
    case "$answer" in
        g|G)
            sudo cp -rv ./Iosevka /etc/fonts/Iosevka
            break
            ;;
        l|L)
            cp -rv ./Iosevka ~/.fonts/Iosevka
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
            ;;
    esac
echo -e "${primary}) Installing local.conf${text}"
sleep 1
read -rp "${secondary}Make departure mono the default sans and mono font? [y/n]: ${text}" answer_local
    case "$answer_local" in
        y|Y)
            case "$answer" in
                g|G)
                    sudo cp -rv ./local.conf /etc/fonts/local.conf
                    break
                    ;;
                l|L)
                    cp -rv ./local.conf ~/.fonts/local.conf
                    break
                    ;;
                *)
                    echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
                    ;;
            esac
            break
            ;;
        n|N)
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'y' (global) or 'n' (local).${text}"
            ;;
    esac
echo -e "${primary}) Refreshing font cache${text}"
sleep 1
    case "$answer" in
        g|G)
            sudo fc-cache -fv
            ;;
        l|L)
            fc-cache -fv
            ;;
        *)
            echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
            ;;
    esac
echo -e "${primary}) Installing cross-platform configs${text}"
sleep 1
cp -rv ./cross-platform/* ~/.config/
echo -e "${primary}) Installing wayland configs${text}"
sleep 1
cp -rv ./wayland/* ~/.config
echo -e "${primary}) Installing shell scripts${text}"
sleep 1
mkdir -pv ~/scripts
cp -vn ./scripts/* ~/scripts/
echo -e "${primary}) Installing wallpapers${text}"
sleep 1
mkdir -pv ~/Pictures
mkdir -pv ~/Pictures/Important
cp -vn ./pictures/* ~/Pictures/Important
echo -e "${primary}) Installing .bashrc${text}"
sleep 1
cat ./.bashrc
cat ./.bashrc >> ~/.bashrc
cat ~/.bashrc
echo -e "${primary}) Building c++ and c scripts${text}"
sleep 1
g++ src/chlebqowy-workspace-bar.cpp -o bin/chlebqowy-workspace-bar
g++ src/chlebqowy-update-num.cpp -o bin/chlebqowy-update-num
g++ src/chlebqowy-gpu-usage-wl.cpp -o bin/chlebqowy-gpu-usage-wl
read -rp "${secondary}Install globally or locally? [g/l]: ${text}" answer_scripts

    case "$answer_scripts" in
        g|G)
            sudo cp -rv bin/chlebqowy-gpu-usage /usr/bin/chlebqowy-gpu-usage
            sudo cp -rv bin/chlebqowy-update-num /usr/bin/chlebqowy-update-num
            sudo cp -rv bin/chlebqowy-workspace-bar-wl /usr/bin/chlebqowy-workspace-bar-wl
            break
            ;;
        l|L)
            cp -rv bin/chlebqowy-gpu-usage ~/.local/bin/chlebqowy-gpu-usage
            cp -rv bin/chlebqowy-update-num ~/.local/bin/chlebqowy-update-num
            cp -rv bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
            ;;
    esac
echo -e "\x1b[32m✓ Finished${text}"
echo -e "${secondary} Please make sure all dependencies from README.md are installed${text}"
echo -e "${secondary} Please reboot after installing them${text}"
