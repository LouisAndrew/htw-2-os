#!/bin/bash

z1=$1
z2=$2
erg=0

while [ $z1 -lt $z2 ]; do
        erg=`expr $z1 + $z2`
        echo $z1 + $z2 = $erg
        z1=`expr $z1 + 1`
done

echo Finalergebnis: $erg

exit 0