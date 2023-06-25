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
        timeout 10s ../zappy_server $line > /dev/null
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
        echo -e "$file: \033[1;32mOK\033[0m"
    else
        printf "\e[1;31m---- %s test fail: Program launched but shouldn't or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
    fi
done

port=$((RANDOM % 500 + 1500))

for file in ./tests/functional/connexion_deconnexion/* ; do
    ((total++))
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    $file $port
    exit_code=$?
    if [ ! $exit_code -eq 0 ]
    then
        printf "\e[1;31m---- %s test fail: Program didn't launched or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
    else
        ((nb_valid++))
        echo -e "$file: \033[1;32mOK\033[0m"
    fi
    ((port++))
done

pid_server=0

launch_server(){
    timeout -s SIGINT --preserve-status 5s ../zappy_server -x 10 -y 10 -n name1 name2 -c 5 -f 80 -p $1 > /dev/null
    exit $?
}

launch_client(){
    timeout 2s netcat 127.0.0.1 $1 < $2 > out.tmp
    exit 0
}

for file in ./tests/functional/gui_tests/*; do
    ((total++))
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    ((port++))
    launch_server $port &
    pid_server=$!
    launch_client $port $file &
    wait $pid_server
    exit_code=$?
    if [ ! $exit_code -eq 0 ]
    then
        printf "\e[1;31m---- %s test fail: Program didn't launched or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
    fi
    tail -n +106 out.tmp > out2.tmp
    sed -n '/bct/!p' out2.tmp > out.tmp
    sed -n '/pin/!p' out.tmp > out2.tmp
    sed -n '/ppo/!p' out2.tmp > out.tmp
    sed -n '/pnw/!p' out.tmp > out2.tmp
    cat out2.tmp > out.tmp
    name=$(basename "$file")
    if !(cmp -s out.tmp ./tests/functional/gui_tests_expected/$name); then
        echo -e "$file: \033[1;31mERROR!\033[0m Output differs"
        diff out.tmp ./tests/functional/gui_tests_expected/$name
        failed=1
    else
        echo -e "$file: \033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
done

for file in ./tests/functional/ai_tests/*; do
    ((total++))
    printf "\e[1;33mStart testing %s ...\e[0m\n" $file
    ((port++))
    launch_server $port &
    pid_server=$!
    launch_client $port $file &
    wait $pid_server
    exit_code=$?
    if [ ! $exit_code -eq 0 ]
    then
        printf "\e[1;31m---- %s test fail: Program didn't launched or crashed (exit code %d) ----\e[0m\n" $file $exit_code
        failed=1
    fi
    tail -n +4 out.tmp > out2.tmp
    cat out2.tmp > out.tmp
    name=$(basename "$file")
    if !(cmp -s out.tmp ./tests/functional/ai_tests_expected/$name); then
        echo -e "$file: \033[1;31mERROR!\033[0m Output differs"
        diff out.tmp ./tests/functional/ai_tests_expected/$name
        failed=1
    else
        echo -e "$file: \033[1;32mOK\033[0m"
        ((nb_valid++))
    fi
done

printf "\e[1;32m---- %d/%d tests valided ----\e[0m\n" $nb_valid $total
if [ $failed -eq 1 ]
then
    exit 1
fi
