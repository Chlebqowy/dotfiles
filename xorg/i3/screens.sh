if [ "$1" = "horizontal" ]; then
	xrandr --output HDMI-0 --mode 2560x1440 --rate 120 --pos 0x0 --rotate normal
	xrandr --output DP-2 --mode 2560x1440 --rate 240 --pos 2560x0 --rotate normal --primary
else
	echo "VERTICAL NOT SET UP" >&2
fi
