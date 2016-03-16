#!/bin/bash
#author: Darío Sierra
#Date: 16 de marzo de 2016


  if [[ $1 == "-help" ]]; then
    AYUDA="El script va pidiendo una serie de datos y actualiza el archivo Makefile ."
    AYUDA+="\nPara conseguir la grafica ejecutar \n make "
    echo -e $AYUDA
    exit
  fi


  echo -e "Nombre de la grafica \t"
  read NOMBRE_GRAFICA

  echo -e "Nombre eje X :"
  read NOMBRE_EJE_X

  echo -e "Nombre eje Y :"
  read NOMBRE_EJE_Y


  echo -e "\n¿Qué tipo de formato quieres? Elige entre los siguientes: \n pdf \t svg \t jpeg \t png"
  read FORMATO

  while [[ $FORMATO != "pdf" &&  $FORMATO != "svg" && $FORMATO != "jpeg" && $FORMATO != "png" ]]; do
    echo -e "\n¿Qué tipo de formato quieres? Elige entre los siguientes: \n pdf \t svg \t jpeg \t png"
    read FORMATO

  done

  echo "Nombre del archivo:"
  read NOMBRE_ARCHIVO


  echo "¿Plot de cuántos archivos?"
  read NUM_ARCHIVOS

  echo -e "Dime el nombre de los archivos. Formato:(sin espacios)archivo(sin espacios) enter ... (sin espacios)archivo(sin espacios) enter "


  for (( i = 0; i < $NUM_ARCHIVOS; i++ )); do
    read TMP
    ARCHIVOS_ARRAY[i]=$TMP
  done

  echo "¿Quiéres unir los puntos (s/n)"
    read FORMATO_PUNTOS




  echo  "set title \"$NOMBRE_GRAFICA\" "    >> gnuplot_script
  echo  "set xlabel \"$NOMBRE_EJE_X\" "     >> gnuplot_script
  echo  "set ylabel \"$NOMBRE_EJE_Y\" "     >> gnuplot_script


  echo  "set term $FORMATO "          >> gnuplot_script
  echo "set output \"$NOMBRE_ARCHIVO.$FORMATO\" " >> gnuplot_script


  if [[ $FORMATO_PUNTOS == 's' ]]; then
    echo "set style data linespoint"  >>gnuplot_script
  fi


  TO_PLOT="plot "

  for (( i = 0; i < $NUM_ARCHIVOS; i++ )); do
    ARCHIVO=${ARCHIVOS_ARRAY[i]}
    TO_PLOT+="\"$ARCHIVO\" "
  done

  echo "¿Quieres cambiar la leyenda de sitio? (s/n)"
  read ANSWER

  if [[ $ANSWER == 's' ]]; then
    echo -e "Dame dos opciones de entre estes (left, right, top, bottom) \n"

    for (( i = 0; i < 2; i++ )); do
      read TMP
      KEY[i]=$TMP
    done

    echo "set key ${KEY[0]} ${KEY[1]}" >> gnuplot_script
  fi

  echo $TO_PLOT >> gnuplot_script

  TO_PLOT="gnu_plot: "

  for (( i = 0; i < $NUM_ARCHIVOS; i++ )); do
    TO_PLOT+=${ARCHIVOS_ARRAY[i]}
    TO_PLOT+=" "
  done

  TO_PLOT+="\n\n\t\tcat gnuplot_script | gnuplot "

  echo -e $TO_PLOT >> Makefile
