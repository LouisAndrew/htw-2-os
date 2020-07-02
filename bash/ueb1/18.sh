#!/bin/bash

faktor=`less zahl.txt`
echo faktor wird von zahl.txt hergenommen
echo $faktor \* 4 = `expr $faktor \* 4`
rm zahl.txt

exit 0