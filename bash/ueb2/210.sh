#!/bin/bash

while [ 1 -ne 0 ]; do

        read line
        i=-1

        for wort in $line; do
                i=`expr $i + 1`
                w[$i]=$wort
        done

        if [ ${w[0]} -eq 0 ]; then
                break
        fi

        echo ${w[*]}

done < read.data

exit 0