# Chlebqowy Dotfiles

<img width="2560" height="1440" alt="i3 (X11) screenshot" src="https://github.com/user-attachments/assets/e10b32f4-96b4-4d5e-a29a-086b195596c8" />
<img width="2560" height="1440" alt="Niri (Wayland) screenshot" src="https://github.com/user-attachments/assets/f1efa861-4f4c-438e-9620-81035c1e5482" />

> [!NOTE]
> AI has been used a bit in this project but all design choices were done by me. [Click here for more info](#ai-disclosure)

## Currently includes
- starship
- kitty/termux
- dunst
- fontconfig
- micro
- swayfx
- 
- feh

## Features


## Keybinds
- All keybinds follow simple patterns such as all system shortcuts starting with super.
### Essential shortcuts:
- Windows can be moved or focused with `Super` + `↑`/`←`/`↓`/`→` or `w`/`a`/`s`/`d`.
- Resizing is done with `Super` + `+` / `-` and `Super` + `Shift` + `+` / `-`
- The terminal is opened with `Super` + `Enter`, Firefox with `Super`+`Shift`+`Enter` and the launcher with `Super` + `i`
- You can focus on the left monitor with `Ctrl` + `Super` + `Left` and on the right with `Ctrl` + `Super` + `Right`

_Please read the [`sway`](wayland/sway/config) config to learn more

## How to install
> [!WARNING]
> Back up your existing `~/.config` and `/etc/fonts` first.

You can install it with `sh install.sh`, manually or `sh autoinstall.sh` (ONLY DO THE LAST ONE IF YOU READ THE SCRIPT).

1. Copy all of the contents of the cross-platform directory into `~/.config`
2. If you want to use X11, also copy all of the contents of the `xorg` directory into `~/.config`     
4. Put scripts into `~/scripts`  
5. Copy all contents of the `bin/` directory into `~/.local/bin` (per-user) or `/usr/bin` (REQUIRES SUDO) (if you don't trust me with the binaries, you can build them yourself. All source files are included and there's a [building section in this readme](#building))
6. Put the contents of `pictures/` into `~/Pictures/Important/`  
7. Add the contents of `.bashrc` to your `~/.bashrc` (needed for the command prompt to work)  
(For other shells follow https://starship.rs/guide/#step-2-set-up-your-shell-to-use-starship)  

> [!NOTE]
> I recommend modifying niri and i3 files to reflect your monitor setup

> [!NOTE]
> The c++ scripts and dmenu are prebuilt only for x86_64. If you use another architecture please compile the programs yourself. More info [here](#building)  
> The .sh scripts are made for bash and might require some modifications for other shells

### Fonts
__A nerd font is heavily recommended.__ You can find some at https://www.nerdfonts.com/font-downloads.    
_Your main font needs to be monospace_     
Put the nerd font into /etc/fonts/font-name (REQUIRES SUDO) or .fonts (Only for one user)  
Optionally, copy the local.conf to /etc/fonts/local.conf (REQUIRES SUDO)    
(This assumes you are using Iosevka, otherwise you have to modify the file)  
  
## Dependencies    
Starship, kitty, dunst, micro-editor    
swayfx, swaybg, nvidia-smi,    
Building (optional): nlohmann_json-devel (workspace-bar), g++, make (dmenu), xlib, xft and xinerama headers (dmenu)   

On opensuse you can automatically install them with `bash opensuse-dependencies.sh` (Also adds my obs repo)

## Configuration
You have to modify the config files manually, although they are fairly simple.  
Some resources I'd recommend are the wikis for each project, such as:  
[starship](https://starship.rs/config/), man pages [dunst](https://man.archlinux.org/man/dunst.5.en) and the [i3wm userguide](https://i3wm.org/docs/userguide.html).  

> [!NOTE]
> I only included apps that I feel like I've fully riced and the rice
> is up to date enough or has roughly the same style as my other apps.
> Also most settings aren't perfect because I don't have much time for ricing.
> I am planning to add a firefox config and rice rofi, sddm and fastfetch and update the superfile config in the future.
> And make the picom animation for resize smoother and make one for moving. Also add a color one and maybe add dimming to open and close.
> Also add blesh and make dunst an exception for picom

## Contributing  
__Please open an issue if something is broken. Format the issue however you want.__  
_I generally don't accept pull requests_, but I'd welcome AMD/Intel GPU support.  
Feature requests are fine.

## Building 
Optional, the files are included pre-built for x86_64  
For c++ files (with the .cpp ending) such as chlebqowy-workspace-bar.cpp and chlebqowy-update-num.cpp, run g++ file.cpp -o file, for example
```sh
g++ src/chlebqowy-workspace-bar.cpp -o bin/chlebqowy-workspace-bar
g++ src/chlebqowy-update-num.cpp -o bin/chlebqowy-update-num
g++ src/chlebqowy-gpu-usage.cpp -o bin/chlebqowy-gpu-usage
(cd src/dmenu && make && mv dmenu ../../bin/dmenu)
```
Make sure you have the [dependencies](#dependencies) required for building  
dmenu_run and dmenu_path is not provided here but you can get it from the [upstream](https://tools.suckless.org/dmenu/) as they haven't been changed

## Credits  
- [i3wm](https://i3wm.org) for getting me into ricing  
- [Unsplash](https://unsplash.com) for the photos  
- [Suckless](https://suckless.org/) for the upstream dmenu  
- Every project for which configs I included  

## AI Disclosure
ChatGPT and Claude helped me when I couldn't find docs, so fontconfig and getting the sway IPC  
This readme hasn't been AI generated but I've had a model proofread it.  

## License
[MIT](LICENSE) for the configs, scripts and my code  
[The Unsplash license](https://unsplash.com/license) for pictures  
[The dmenu license](src/dmenu/LICENSE) for the dmenu fork  
