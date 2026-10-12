#if type "xrandr"; then
#  for m in $(xrandr --query | grep " connected" | cut -d" " -f1); do
#    MONITOR=$m polybar --reload example &
#  done
#else
#  polybar --reload example &
#fi
#MONITOR="HDMI-1"
#polybar --reload
MONITOR="DP-0" polybar --reload &
MONITOR="HDMI-1" polybar --reload &
