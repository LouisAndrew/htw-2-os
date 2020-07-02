#!/bin/bash

z1=$1
op=$2
z2=$3

if [ "$op" = "/" -a $z2 -eq 0 ]; then
        echo Error: Division durc Null!
else
        echo $z1 $op $z2 = `expr $z1 $op $z2`
fi

exit 0