#!/bin/bash

source /home/user/scripts/wallpapers.sh
mode="--bg-scale"

while true; do
    currentHour=$(date +%H)
    for i in "${!timePeriods[@]}"; do
        if [ "$currentHour" -ge "${timePeriodStarts[$i]}" ]; then
            if [ "$currentTimePeriod" != "${timePeriods[$i]}" ]; then
                currentTimePeriod="${timePeriods[$i]}"
                pkill feh
                echo -e "feh $basedir${wallpapers[$i]} $mode &" 
                feh $basedir${wallpapers[$i]} $mode &
                echo "${timePeriods[$i]}"
                break
            fi
            break
        fi
    done
    sleep 5
done
