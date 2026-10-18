# Chlebqowy Dotfiles

<img width="2560" height="1440" alt="i3 setup" src="https://github.com/user-attachments/assets/d3411e8a-8b31-44ad-885e-9d75b0a008ae" />
<!-- add niri ss -->

> [!NOTE]
> AI has been used a bit in this project but all design choices were done by me. [Click here for more info](#ai-disclosure)

## Currently includes
__Cross-platform__
- starship
- kitty
- dunst
- fontconfig

|X11|Wayland|
|---|---|
|i3|niri|
|polybar|waybar|
|dmenu|rofi (defaults)|
|feh|swaybg|
|picom|built-in|

## Features

### Cross-platform
- Semi-minimalist style with a lot of roundness, thick borders, some transparency and blur
- Fresh green color scheme with many shades.
- Config files that are easy to modify
- Nice wallpapers of nature that change depending on the time of day

### X11
- Quick and clean custom animations
- Compositor shadows, blur and transparency
- Top bar with system info created using polybar
- Polybar module that lists the amount of packages to upgrade
- A separate bar for workspaces on the second screen made with a custom program
- Many custom scripts
- Modified version of dmenu included in the [bin/](bin) directory (x86_64 only)

### Wayland
- Smooth shadows, blur, transparency and animations
- Bar with an experimental design style and the same information as X11
- Tab indicators and notifications that are colored after the app icon
- Some windows moving slightly up and down
- Everything under Cross-platform applies here too

## Keybinds
- All keybinds follow simple patterns such as all system shortcuts starting with super.
- The Niri keybinds are made so that they can work if you have a
single hand on the keyboard and the other on the mouse
or both hands on the keyboard.
### Essential shortcuts:
- Windows can be moved or focused with `Super` + `↑`/`←`/`↓`/`→` or `w`/`a`/`s`/`d`.
- Resizing is done with `Super` + `+` / `-` and `Super` + `Shift` + `+` / `-`
- The terminal is opened with `Super` + `Enter`, Firefox with `Super`+`Shift`+`Enter` and the launcher with `Super` + `i`
- You can focus on the left monitor with `Ctrl` + `Super` + `Left` and on the right with `Ctrl` + `Super` + `Right`

_Please read the [`Niri`](wayland/niri/config.kdl) or [`i3`](xorg/i3/config) configs to learn more_

## How to install
> [!WARNING]
> Back up your existing `~/.config` and `/etc/fonts` first.

1. Copy all of the contents of the cross-platform directory into `~/.config`
2. If you want to use X11, also copy all of the contents of the `xorg` directory into `~/.config`    
3. If you want to use Wayland, also copy all of the contents of the `wayland` directory into `~/.config`  
4. Put scripts into `~/scripts`  
5. (Currently X11-only) Copy all contents of the `bin/` directory into `~/.local/bin` (per-user) or `/usr/bin` (REQUIRES SUDO) (if you don't trust me with the binaries, you can build them yourself. All source files are included and there's a [building section in this readme](#building))
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
I personally use and recommend Departure Mono but it is a pixel font.    
Put the nerd font into /etc/fonts/font-name (REQUIRES SUDO) or .fonts (Only for one user)  
Optionally, copy the local.conf to /etc/fonts/local.conf (REQUIRES SUDO)    
(This assumes you are using Departure Mono, otherwise you have to modify the file)  
  
## Dependencies    
Both: Starship, kitty, dunst    
X11: i3wm/i3 (4.22 or newer, or i3-gaps on older distros), i3bar, picom, polybar, feh, nvidia-smi (optional)  
Wayland: niri, waybar, swaybg, rofi  
Building (optional): nlohmann_json-devel (workspace-bar), g++, make (dmenu), xlib, xft and xinerama headers (dmenu)   

## Configuration
You have to modify the config files manually, although they are fairly simple.  
Some resources I'd recommend are the wikis for each project, such as:  
[niri](https://github.com/niri-wm/niri/wiki/) [polybar](https://github.com/polybar/polybar/wiki) [starship](https://starship.rs/config/), man pages [dunst](https://man.archlinux.org/man/dunst.5.en) and the [i3wm userguide](https://i3wm.org/docs/userguide.html).  

> [!NOTE]
> I only included apps that I feel like I've fully riced and the rice
> is up to date enough or has roughly the same style as my other apps.
> Also most settings aren't perfect because I don't have much time for ricing.
> I am planning to add a code editor and rice rofi and update the superfile config in the future.

## Contributing  
__Please open an issue if something is broken. Format the issue however you want.__  
_I generally don't accept pull requests_, but I'd welcome AMD/Intel GPU support.  

## Building 
Optional, the files are included pre-built for x86_64
For c++ files (with the .cpp ending) such as workspace-bar.cpp and pkg.cpp, run g++ file.cpp -o file, for example
```sh
g++ scripts/workspace-bar.cpp -o scripts/workspace-bar
g++ src/chlebqowy-update-num/pkg.cpp -o bin/chlebqowy-update-num
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
ChatGPT and Claude for helping me when I couldn't find docs, so:  
fontconfig, new picom syntax, and getting the i3 IPC  
and to troubleshoot waybar and niri  
This readme hasn't been AI generated but I've had a model proofread it.  

## License
[MIT](LICENSE) for the configs, scripts and my code  
[The Unsplash license](https://unsplash.com/license) for pictures  
[The dmenu license](src/dmenu/LICENSE) for the dmenu fork  
