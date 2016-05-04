#!/bin/bash
# Uso: nombredelejecutable inicial salto final modo
# Ejemplo: posicion 10 5 80 t ejecuta posicion 10 t, posicion 15 t, ..., posicion 80 t
# Salida: nombredelejecutable_modo.dat

> $(basename $1 .exe)_$5.dat

for i in $(seq $2 $3 $4); do
  ./$1 $i $5 >> $(basename $1 .exe)_$5.dat
done
