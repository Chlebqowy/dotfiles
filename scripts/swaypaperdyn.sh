#!/bin/bash

folder=$(dirname "$0")
source $folder/wallpapers.sh
mode="fill"

while true; do
    currentHour=$(date +%H)
    for i in "${!timePeriods[@]}"; do
        if [ "$currentHour" -ge "${timePeriodStarts[$i]}" ]; then
            if [ "$currentTimePeriod" != "${timePeriods[$i]}" ]; then
                currentTimePeriod="${timePeriods[$i]}"
                pkill swaybg
                swaybg -i "$basedir${wallpapers[$i]}" -m $mode &
                echo "${timePeriods[$i]}"
                break
            fi
            break
        fi
    done
    sleep 5
done
