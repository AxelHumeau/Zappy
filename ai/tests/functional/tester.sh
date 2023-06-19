#!/usr/bin/bash

nb_valid=0
validity=0
total=0

for file in ./tests/functional/bad_arguments/* ; do
    ((total++))
    validity=0
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    while IFS=$'\n' read -r line; do
        if [[ "$1" == "-v" ]]
        then
            printf "checking command: ../zappy_ai %s\n" "$line"
        fi
        timeout 10s coverage run ./zappy_ai $line > /dev/null 2>&1
        if [ ! $? -eq 84 ]
        then
            validity=1
            break
        fi
    done < $file
    if [ $validity -eq 0 ]
    then
        ((nb_valid++))
    else
        printf "\e[1;31m---- %s test fail: Program launched but shouldn't ----\e[0m\n"
        break
    fi
done

printf "\e[1;32m---- %d/%d tests valided ----\e[0m\n" $nb_valid $total
