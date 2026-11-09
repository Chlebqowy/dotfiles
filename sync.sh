#!/bin/bash
cp -v ~/.config/sway/config ./wayland/sway/
cp -v ~/.config/rofi/themes/chlebqowy-light.rasi ./wayland/rofi/themes/
cp -v ~/.config/rofi/themes/config.rasi ./wayland/rofi/
cp -v ~/.config/dunst/dunstrc ./cross-platform/dunst/
cp -v ~/.config/kitty/kitty.conf ./cross-platform/kitty/
cp -v ~/.config/micro/bindings.json ./cross-platform/micro/
cp -v ~/.config/micro/settings.json ./cross-platform/micro/
cp -v ~/.config/micro/syntax/notatka.yaml ./cross-platform/micro/syntax/
cp -v ~/.config/micro/colorschemes/chlebqowy-light.micro ./cross-platform/micro/colorschemes/
cp -v ~/.config/starship.toml ./cross-platform/
cp -v ~/scripts/wallpapers.sh ./scripts
cp -v ~/scripts/swaypaperdyn.sh ./scripts
cp -v ~/Pictures/Wallpapers/* ./pictures/Wallpapers
cp -rv /boot/grub2/themes/* ./global/grub2/
cp -v /etc/greetd/* ./global/greetd/
