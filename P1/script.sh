#!/bin/bash
# Uso: nombredelejecutable inicial salto final
# Ejemplo: fibonacci 10 5 80 ejecuta fibonacci 10, fibonacci 15, ..., fibonacci 80
# Salida: nombredelejecutable_output.txt

> $(basename $1 .exe).dat

for i in $(seq $2 $3 $4); do
  ./$1 $i >> $(basename $1 .exe).dat
done
