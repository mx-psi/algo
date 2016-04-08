@echo off
REM Uso: nombredelejecutable inicial salto final modo
REM Ejemplo: posicion 10 5 80 t ejecuta posicion 10 t, posicion 15 t, ..., posicion 80 t
REM Salida: nombredelejecutable_modo.dat

break > %~n1.dat
for /l %%x in (%2, %3, %4) do %1 %%x %5 >> %~n1_%5.dat
