# Chlebqowy Dotfiles

<img width="2560" height="1440" alt="i3 setup" src="https://github.com/user-attachments/assets/d3411e8a-8b31-44ad-885e-9d75b0a008ae" />
// add niri ss

## Currently includes:
- niri, waybar
- i3wm, picom, polybar
- starship, kitty, dunst
- dmenu
- swaybg/feh

-------

## Features:

### Cross-platform
- Cool terminal and prompt that shows all important data in a nice way
- Clean notifications
- Semi-minimalist vibe with a lot of roundness, thick borders, some transparency and blur
- Nice green color scheme (maybe add more in the future)
- Dotfiles that are easy to modify
-------
### X11:
- Nice, quick and smooth custom animations
- i3wm config that's nice to use
- A top bars that display some data that's always useful
- A seperate workspace bar with named workspaces
- Wallpapers depending on the time of day
- Polybar module that list packages to upgrade
- Custom scripts and dmenu modifications
- Nice nature wallpapers
-----
### Wayland:
- Sensible niri keybinds, usable with both hands or the keyboard or one on the mouse
- Good smooth shadows
- Wallpapers depending on the time of day
- Bar with an interesting design style and the same information as x11
- Nice nature wallpapers
-----
## How to install:
> [!WARNING]
> Back up your existing `~/.config` and `/etc/fonts` first.

__A nerd font is heavily recommended.__ You can find some at https://www.nerdfonts.com/font-downloads.
_Your main font needs to be monospace_
I personally use and recommend Departuremono but it is a pixel font.
Put the nerd font into /etc/fonts/font-name
Optionally, copy the local.conf to /etc/fonts/local.conf (REQUIRES SUDO)
(This assumes you are using departuremono, otherwise you have to modify the file)

Copy all of the contents of the cross-platform directory into ~/.config
If you want to use x11, also copy all of the contents of the x11 directory into ~/.config
If you want to use wayland, also copy all of the contents of the x11 directory into ~/.config

Put scripts into ~/scripts
Copy all contents of the bin/ directory into /usr/bin/ (REQUIRES SUDO) or .local/bin
Put the contents of pictures/ into ~/Pictures/Important/
Add the contents of .bashrc to your .bashrc
(For other shells follow https://starship.rs/guide/#step-2-set-up-your-shell-to-use-starship)
---
## Dependencies
Both: Starship, kitty, dunst
X11: i3-gaps, i3bar, picom, polybar, nvidia-smi, nlohmann_json-devel
Wayland: niri, waybar

### Configuration
You have to modify the config files manually, although they are fairly simple.
Some resources I'd recommend are the wikis for each project and the i3wm manual.

### Please open an issue if something is broken.
__I don't accept pull requests__

_The bashrc is needed for starship to apply_

> [!NOTE]
> I only included apps that I feel like I've fully riced and the rice
> is up to date enough or has roughly the same style as my other apps._
> Also most settings aren't perfect because I don't have much time for ricing.
> I am planning to add a code editor and rofi and update the spf config in the future.
