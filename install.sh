primary=$'\e[38;2;117;255;152m'
secondary=$'\e[38;2;79;218;88m'
text=$'\e[38;2;251;254;252m'

mkdir -pv ~/.config
mkdir -pv ~/.fonts #most likely exist but I have to make sure
echo -e "${primary}) Backing up ~/.config to ~/.config-backup-chlebqowy${text}"
sleep 1
cp -rv ~/.config ~/config-backup-chlebqowy
echo -e "${primary}) Backing up ~/.fonts to ~/.fonts-backup-chlebqowy${text}"
sleep 1
cp -rv ~/.fonts ~/.fonts-backup-chlebqowy
echo -e "${primary}) Backing up /etc/fonts to /etc/fonts-backup-chlebqowy (REQUIRES SUDO, OPTIONAL)${text}"
sleep 1
sudo cp -rv /etc/fonts /etc/fonts-backup-chlebqowy
echo -e "${primary})Installing departure mono${text}"
sleep 1
read -rp "${secondary}Install globally or locally? [g/l]: ${text}" answer

    case "$answer" in
        g|G)
            sudo cp -rv ./departure_mono_nerd.otf /etc/fonts/departure_mono_nerd.otf
            break
            ;;
        l|L)
            cp -rv ./departure_mono_nerd.otf ~/.fonts/departure_mono_nerd.otf
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
            ;;
    esac
echo -e "${primary})Installing local.conf${text}"
sleep 1
read -rp "${secondary}Make departure mono the default sans and mono font? [y/n]: ${text}" answer-local
    case "$answer-local" in
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
echo -e "${primary})Installing cross-platform configs${text}"
sleep 1
cp -rv ./cross-platform/* ~/.config/
echo -e "${primary})Installing display server-specific configs${text}"
sleep 1
read -rp "${secondary}Xorg, Wayland or both? [x/w/b]: ${text}" answer_display
    case "$answer_display" in
        w|W)
            sudo cp -rv ./wayland/* ~/.config
            break
            ;;
        x|X)
            sudo cp -rv ./xorg/* ~/.config
            break
            ;;
        b|B)
            sudo cp -rv ./xorg/* ~/.config
            sudo cp -rv ./wayland/* ~/.config
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'w' (Wayland), 'X' (Xorg) or 'b' (both).${text}"
            ;;
    esac
echo -e "${primary})Installing shell scripts${text}"
sleep 1
mkdir -pv ~/scripts
cp -vn ./scripts/* ~/scripts/
echo -e "${primary})Installing wallpapers${text}"
sleep 1
mkdir -pv ~/Pictures
mkdir -pv ~/Pictures/Important
cp -vn ./pictures/* ~/Pictures/Important
echo -e "${primary})Building c++ and c scripts${text}"
sleep 1
g++ src/chlebqowy-workspace-bar.cpp -o bin/chlebqowy-workspace-bar
g++ src/chlebqowy-update-num.cpp -o bin/chlebqowy-update-num
g++ src/chlebqowy-gpu-usage.cpp -o bin/chlebqowy-gpu-usage
read -rp "${secondary}Install globally or locally? [g/l]: ${text}" answer-scripts

    case "$answer-scripts" in
        g|G)
            sudo cp -rv bin/chlebqowy-gpu-usage /usr/bin/chlebqowy-gpu-usage
            sudo cp -rv bin/chlebqowy-update-num /usr/bin/chlebqowy-update-num
            sudo cp -rv bin/chlebqowy-workspace-bar /usr/bin/chlebqowy-workspace-bar
            break
            ;;
        l|L)
            sudo cp -rv bin/chlebqowy-gpu-usage .local/bin/chlebqowy-gpu-usage
            sudo cp -rv bin/chlebqowy-update-num .local/bin/chlebqowy-update-num
            sudo cp -rv bin/chlebqowy-workspace-bar .local/bin/chlebqowy-workspace-bar
            break
            ;;
        *)
            echo -e "${secondary}Please enter 'g' (global) or 'l' (local).${text}"
            ;;
    esac
echo -e "${primary})Installing dmenu${text}"
sleep 1
cd src/dmenu
make
case "$answer-scripts" in
	g|G)
		sudo mv -v dmenu /usr/bin/dmenu
	l|L)
		mv -v dmenu .local/bin/dmenu
	*)
	    mv -v dmenu .local/bin/dmenu
cd ../..
read -rp "${secondary}Get pre-build dmenu_run and dmenu_path or install it manually? [p/m]: ${text}" answer-dmenu
	case "$answer-dmenu" in
        p|P)
        	case "$answer-scripts" in
        		g|G)
        			sudo mv -v dmenu_run /usr/bin/dmenu_run
        			sudo mv -v dmenu_path /usr/bin/dmenu_path
        		l|L)
        			mv -v dmenu_run .local/bin/dmenu_run
        			mv -v dmenu_path .local/bin/dmenu_path
        		*)
        	    	mv -v dmenu_run .local/bin/dmenu_run
        	    	mv -v dmenu_path .local/bin/dmenu_path
            ;;
        m|M)
			echo -e "${primary})Please get dmenu_run and dmenu_path from the suckless website and put them in /usr/bin or ~/.local/bin (depening on whether you installed the c scripts globally or locally)${text}"
            ;;
        *)
            echo -e "${secondary}Please enter 'p' (pre-built) or 'm' (manual).${text}"
            ;;
    esac
echo -e "\x1b[32m✓ Finished${text}"
echo -e "${secondary} Please make sure all dependencies from README.md are installed${text}"
