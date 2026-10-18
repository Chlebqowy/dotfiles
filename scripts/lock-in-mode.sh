#!/bin/sh
if [ "$1" = "on" ]; then
    pkill picom
    i3-msg gaps inner all set 2
    i3-msg gaps outer all set 2
    while true; do
        i3-msg '[class="^.*"] border pixel 2'
        sleep 0.5
    done
elif [ "$1" = "off" ]; then
    picom &
    i3-msg gaps inner all set 20 
    i3-msg gaps outer all set 5
    i3-msg '[class="^.*"] border pixel 8'
    disown
    pkill "lock-in-mode"
    exit
else
    echo "Incorrect args. Use on or off."
fi