#!/usr/bin/bash

nb_valid=0
validity=0
total=0
failed=0
exit_code=0

for file in ./tests/functional/bad_arguments/* ; do
    ((total++))
    validity=0
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    while IFS=$'\n' read -r line; do
        if [[ "$1" == "-v" ]]
        then
            printf "checking command: ../zappy_server %s\n" "$line"
        fi
        timeout 10s ../zappy_server $line > /dev/null 2>&1
        exit_code=$?
        if [ ! $exit_code -eq 84 ]
        then
            validity=1
            break
        fi
    done < $file
    if [ $validity -eq 0 ]
    then
        ((nb_valid++))
    else
        printf "\e[1;31m---- %s test fail: Program launched but shouldn't or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
        break
    fi
done

port=$((RANDOM % 500 + 1500))

for file in ./tests/functional/connexion_deconnexion/* ; do
    ((total++))
    validity=0
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    $file $port
    exit_code=$?
    if [ ! $exit_code -eq 0 ]
    then
        printf "\e[1;31m---- %s test fail: Program didn't launched or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
        break
    else
        ((nb_valid++))
    fi
    ((port++))
done

printf "\e[1;32m---- %d/%d tests valided ----\e[0m\n" $nb_valid $total
if [ $failed -eq 1 ]
then
    exit 1
fi
