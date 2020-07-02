#!/bin/bash

echo Anzahl von Argumenten: $#
echo Liste aller Argumente: $@
echo ProzessID: $$

a=$1
b=$2

echo Argument 1 + Argument 2 = $a + $b = `expr $a + $b`

exit 0