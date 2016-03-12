@echo off
REM Uso: nombredelejecutable nombre_eje_x nombre_eje_y nombre_titulo nombre_leyenda
REM Ejemplo: script_plot_config burbuja "Capacidad del vector" "Tiempos de ejecución" "Tiempos de ejecución de burbuja" "burbuja"
REM Salida: plot_nombredelejecutable.plg

(
   echo set title "%~2"
   echo set xlabel "%~3"
   echo set ylabel "%~4"
   echo plot data title "%~n5"
) > plot_%~n1.plg
