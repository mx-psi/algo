#!/bin/bash
# Uso: datos salida
# Ejemplo: burbuja.dat burbuja.png
# Salida: salida
# Ejemplo de salida: burbuja.png

PLOT_NAME=${2%.*}
gnuplot -e "data='$1'" -e "out='$2'" plot_$PLOT_NAME.plg
rm plot_$PLOT_NAME.plg
