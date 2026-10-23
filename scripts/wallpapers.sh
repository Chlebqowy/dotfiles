#!/bin/bash

# has to go from starts last to starts first
timePeriods=("Night" "Day" "Night")
wallpapers=("wpaper-light.png" "wpaper-light.png" "wpaper-light.png")
timePeriodStarts=(18 6 0)
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
