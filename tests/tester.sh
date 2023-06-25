#!/usr/bin/bash

launch_server(){
    timeout -s SIGINT --preserve-status 45s ./zappy_server -x $2 -y $3 -n name1 name2 -c 5 -f 100 -p $1 > /dev/null
    exit $?
}

launch_gui_client(){
    timeout 45s ./zappy_gui -h 127.0.0.1 -p $1 > /dev/null
    exit $?
}

launch_ai_client(){
    cd ai
    timeout 15s coverage run ./zappy_ai -h 127.0.0.1 -p $1 -n $2 > /dev/null
    exit $?
}

port=$((RANDOM % 500 + 2000))
failed=0
total=0
nb_valid=0

pid_server=0
pid_gui=0
pid_ai1=0
pid_ai2=0
pid_ai3=0
pid_ai4=0

while IFS=$'\n' read -r line; do
    if [[ "$1" == "-v" ]]
    then
        printf "checking with size: %s" "$line"
    fi

    launch_server $port $line &
    pid_server=$!
    launch_gui_client $port &
    pid_gui=$!

    printf "\e[1;33mStart testing with 1 ai ...\e[0m\n"
    launch_ai_client $port name1 &
    pid_ai1=$!
    wait $pid_ai1
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (1 ai) test fail: Ai didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))

    printf "\e[1;33mStart testing with 2 ai ...\e[0m\n"
    launch_ai_client $port name1 &
    pid_ai1=$!
    launch_ai_client $port name1 &
    pid_ai2=$!
    wait $pid_ai1
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai) test fail: First ai didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))
    wait $pid_ai2
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai) test fail: Second ai didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))

    printf "\e[1;33mStart testing with 2 ai in each team...\e[0m\n"
    launch_ai_client $port name1 &
    pid_ai1=$!
    launch_ai_client $port name1 &
    pid_ai2=$!
    launch_ai_client $port name2 &
    pid_ai3=$!
    launch_ai_client $port name2 &
    pid_ai4=$!
    wait $pid_ai1
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai in each team) test fail: First ai of team 'name1' didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))
    wait $pid_ai2
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai in each team) test fail: Second ai of team 'name1' didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))
    wait $pid_ai3
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai in each team) test fail: First ai of team 'name2' didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))
    wait $pid_ai4
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- (2 ai in each team) test fail: Second ai of team 'name2' didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))

    printf "\e[1;33mVerifiying GUI exit status...\e[0m\n"
    wait $pid_gui
    exit_code=$?
    if [[ ! $exit_code -eq 124 && ! $exit_code -eq 0 ]]
    then
        failed=1
        printf "\e[1;31m---- Gui didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))

    printf "\e[1;33mVerifiying server exit status...\e[0m\n"
    wait $pid_server
    exit_code=$?
    if [ ! $exit_code -eq 0 ]
    then
        failed=1
        printf "\e[1;31m---- Server didn't launched or crashed (exit code %d) ----\e[0m\n" $exit_code
    else
        echo -e "\033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
    ((total++))

    ((port++))
done < ./tests/parameters

printf "\e[1;32m---- %d/%d tests valided ----\e[0m\n" $nb_valid $total
if [ $failed -eq 1 ]
then
    exit 1
fi
