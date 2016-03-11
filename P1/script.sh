#!/bin/bash
# Uso: nombredelejecutable inicial salto final
# Ejemplo: fibonacci 10 5 80 ejecuta fibonacci 10, fibonacci 15, ..., fibonacci 80
# Salida: nombredelejecutable_output.txt
for i in {$2..$3..$4} do
  echo $i | $1 >> $1_output.txt
done
