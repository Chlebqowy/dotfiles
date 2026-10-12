#!/bin/bash

# has to go from starts last to starts first
timePeriods=("Night" "Evening" "Midday" "Day" "Morning" "Night" "Late Night" "3am" "Late Night" "Night")
wallpapers=("wpapernight.jpg" "wpaperevening.jpg" "wpapermidday.jpg" "wpaper.jpg" "wpapermorning.jpg" "wpapernight.jpg" "wpapermidnight.jpg" "wpaperspecial.jpg" "wpapermidnight.jpg" "wpapernight.jpg")
timePeriodStarts=(21 18 15 12 9 7 4 3 1 0)
basedir="/home/user/Pictures/Important/"

if [ ${#timePeriods[@]} != ${#wallpapers[@]} ]; then
	echo "ERROR: Amount of time periods does not match amount of wallpapers (${#timePeriods[@]}, ${#wallpapers[@]})" >&2
    exit 1
fi
if [ ${#timePeriods[@]} != ${#timePeriodStarts[@]} ]; then
	echo "ERROR: Amount of time periods does not match amount of period starting marks (${#timePeriods[@]}, ${#timePeriodStarts[@]})" >&2
    exit 1
fi

currentTimePeriod="None"
