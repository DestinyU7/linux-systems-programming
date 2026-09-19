#!/bin/bash

# does not account for neg numbers
sci_notation_regex='^[0-9]+([.][0-9]+)?(e[0-9]+|e-[0-9]+)?$'

function test_time {
    # compare 
    if [[ ! $1 =~ $sci_notation_regex ]] ; 
    then
        echo ERROR: time is not on stderr or not formatted properly
        echo
        rm .time
        exit 1
    fi

    # delete tmp file 
    rm .time
}


if [ -e .passed_"$1" ] ; 
then
    rm .passed_"$1"
fi


while read test; 
do

    t=($test)
    len=${#t[@]}  # Get the length of the array
    last_index=$((len - 1))  # Calculate the last index
    
    echo ${t[$last_index]} ${t[0]} ${t[1]} ${t[2]} ${t[3]} ${t[4]} ${t[5]}
    # correctness
    ANSW=$(./"$1"_sched ${t[0]} 0 10 ${t[1]} ${t[2]} ${t[3]} ${t[4]} ${t[5]}  2> .time)  

    if ./approx ${ANSW} ${t[$last_index]};
    then
        test_time $(cat .time)

    else # display error and quit
        echo FAIL: "./"$1"_sched ${t[0]} 0 10 ${t[1]} ${t[2]} ${t[3]} ${t[4]}" should give roughly "${t[$last_index]}" not ${ANSW}
        exit 1
    fi

done < "$2" 


touch .passed_"$1"


# all tests passed
echo ================================
echo
echo Success! All tests passed! ":)"
