@echo off
REM Uso: nombredelejecutable inicial salto final
REM Ejemplo: fibonacci 10 5 80 ejecuta fibonacci 10, fibonacci 15, ..., fibonacci 80
REM Salida: nombredelejecutable_output.txt
for /l %%x in (%2, %3, %4) do echo %%x | %1 >> %1_output.txt