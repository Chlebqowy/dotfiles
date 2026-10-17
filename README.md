# Chlebqowy Dotfiles

<img width="2560" height="1440" alt="i3 setup" src="https://github.com/user-attachments/assets/d3411e8a-8b31-44ad-885e-9d75b0a008ae" />
<!-- add niri ss -->

^(note: AI has been used a bit in this project but all design choices were done by me. Scroll down to the bottom for more info)

## Currently includes:
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

---

## Features:

### Cross-platform
- Semi-minimalist style with a lot of roundness, thick borders, some transparency and blur
- Fresh green color scheme with many shades.
- Config files that are easy to modify
- Nice wallpapers of nature that change depending on the time of day (From unsplash)
---
### X11:
- Quick and clean custom animations
- Compositor shadows, blur and transparency
- Top bar with system info created using polybar
- Polybar module that list the amount of packages to upgrade
- A seperate bar for workspaces on the second screen made with a custom program
- Many custom scripts
- Modified version of dmenu
---
### Wayland:
- Smooth shadows, blur, transparency and animations
- Bar with an experimental design style and the same information as x11
- Tab indicators and notification that are colored after the app
- Certain windows moving ambiently
- Everything under Cross-platform applies here too
---

## Keybinds
- All keybinds follow simple patterns such as all system shortcuts starting with super.
- The Niri keybinds are made so that they can work if you have a
single hand on the keyboard and the other on the mouse
or both hands on the keyboard.
### Essential shortcuts:
- Windows can be moved or focused with super + arrow keys or wasd.
- Resizing is done with Super + + / - and Super + Shift + + / -
- The terminal is opened with Super+Enter, firefox with
Super+Shift+Enter and the launcher with Super+i
- You can focus on the left monitor with Ctrl+Super+Left and on the right with Ctrl+Super+Right

_Please read the [`Niri`](wayland/niri/config.kdl) or [`i3`](xorg/i3/config) configs to learn more_
---
## How to install:
> [!WARNING]
> Back up your existing `~/.config` and `/etc/fonts` first.
> [!NOTE]
> I recommend modifying niri and i3 files to reflect your monitor setup

1. Copy all of the contents of the cross-platform directory into `~/.config    
2. If you want to use x11, also copy all of the contents of the `xorg` directory into `~/.config`    
3. If you want to use wayland, also copy all of the contents of the `wayland` directory into `~/.config`  

4. Put scripts into `~/scripts  `
5. Copy all contents of the `bin/` directory into `/usr/bin/` (REQUIRES SUDO) or `~/.local/bin  `
6. Put the contents of `pictures/` into `~/Pictures/Important/`  
7. Add the contents of `.bashrc` to your `~/.bashrc` (needed for the command prompt to work)  
(For other shells follow https://starship.rs/guide/#step-2-set-up-your-shell-to-use-starship)  

### Fonts
__A nerd font is heavily recommended.__ You can find some at https://www.nerdfonts.com/font-downloads.  
_Your main font needs to be monospace_   
I personally use and recommend Departuremono but it is a pixel font.  
Put the nerd font into /etc/fonts/font-name  
Optionally, copy the local.conf to /etc/fonts/local.conf (REQUIRES SUDO)  
(This assumes you are using departuremono, otherwise you have to modify the file)
---
## Dependencies
Both: Starship, kitty, dunst
X11: i3-gaps, i3bar, picom, polybar, nvidia-smi
Wayland: niri, waybar
Building: nlohmann_json-devel, g++
---
## Configuration
You have to modify the config files manually, although they are fairly simple.
Some resources I'd recommend are the wikis for each project, such as:
[niri](https://github.com/niri-wm/niri/wiki/) [polybar](https://github.com/polybar/polybar/wiki) [starship](https://starship.rs/config/)
, man pages [dunst](https://man.archlinux.org/man/dunst.5.en)
and the [i3wm userguide](https://i3wm.org/docs/userguide.html).
---
## Contributing
### Please open an issue if something is broken. Format the issue however you want.
__I don't accept pull requests__
---
> [!NOTE]
> I only included apps that I feel like I've fully riced and the rice
> is up to date enough or has roughly the same style as my other apps.
> Also most settings aren't perfect because I don't have much time for ricing.
> I am planning to add a code editor and rofi and update the spf config in the future.
---
## Building
If the file ends with .cpp, just run g++ file.cpp -o file
Otherwise, you don't need to build it
---
## Credits
i3wm for getting me into ricing
Unsplash for the photos
MIT for the license
dmenu developers for the upstream dmenu
Every project for which configs I included
ChatGPT and Claude for helping me when I couldn't find docs, so:
fontconfig, new picom syntax, and getting the i3 IPC
and to troubleshoot waybar and niri
All stylistic choices were done by me
This readme hasn't been AI generated but I've had a model proofread it.
