#!/bin/bash

source ~/scripts/wallpapers.sh
mode="--bg-scale"

while true; do
    currentHour=$(date +%H)
    for i in "${!timePeriods[@]}"; do
        if [ "$currentHour" -ge "${timePeriodStarts[$i]}" ]; then
            if [ "$currentTimePeriod" != "${timePeriods[$i]}" ]; then
                currentTimePeriod="${timePeriods[$i]}"
                pkill feh
                feh "$basedir${wallpapers[$i]}" $mode &
                echo "${timePeriods[$i]}"
                break
            fi
            break
        fi
    done
    sleep 5
done
