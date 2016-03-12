#!/bin/bash
# Uso: nombredelejecutable nombre_eje_x nombre_eje_y nombre_titulo nombre_leyenda
# Ejemplo: ./script_plot_config.sh burbuja "Capacidad del vector" "Tiempos de ejecución" "Tiempos de ejecución de burbuja" "burbuja"
# Salida: plot_nombredelejecutable.plg

NAME=${1%.*}
LABELX=$2
LABELY=$3
TITLE=$4
LEGEND=${5%.*}
echo 'set title '\"$TITLE\"'
set xlabel '\"$LABELX\"'
set ylabel '\"$LABELY\"'
plot data title '\"$LEGEND\"'' > plot_$NAME.plg
	
