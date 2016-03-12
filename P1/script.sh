#!/bin/bash
# Uso: nombredelejecutable inicial salto final
# Ejemplo: fibonacci 10 5 80 ejecuta fibonacci 10, fibonacci 15, ..., fibonacci 80
# Salida: nombredelejecutable_output.txt

> $(basename $1 .exe).dat

#for (( i = $2; i < $4; i+=$3 )); do
#  ./$1 $i >> $(basename $1 .exe).dat
#done

#teneis una forma mu rara de hacer los for chavales. Jose, seguro que has sido tú.

for i in $(seq $2 $3 $4); do
  ./$1 $i >> $(basename $1 .exe).dat
done
