CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard cpps/*.cpp)
DATS = $(CPPS:cpps/%.cpp=dats/%.dat)
GPHS = $(CPPS:cpps/%.cpp=img/%_g.pdf)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat
	BAR = \\
else
	SCRIPT = ./script.sh
	BAR = /
endif

all: PresentacionP1.pdf MemoriaP1.pdf
.PHONY: img all clean mrproper
.PRECIOUS: $(DATS) $(GPHS)

exes: $(CPPS:cpps/%.cpp=%.exe)
img: $(GPHS)

%.exe: cpps/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dats/%.dat: %.exe
	$(SCRIPT) $< 2000 2000 50000

img/comparativa_cuadraticos_g.pdf: burbuja.dat seleccion.dat insercion.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos cuadráticos'" plot_multiple.plg

img/comparativa_logaritmicos_g.pdf: quicksort.dat heapsort.dat mergesort.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos n·log(n)'" plot_multiple.plg

img/comparativa_global_g.pdf: quicksort.dat heapsort.dat mergesort.dat burbuja.dat seleccion.dat insercion.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución de globales'" gnuplot_script_cuad

img/%_g.pdf: dats/%.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución \
	de $(basename $< .dat)'; LEGEND='$(basename $< .dat)'" plot.plg

img/%_todos_g.pdf: dats/%_pablo.dat #Añadir resto de nombres
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución para $(basename $@ _todos_g.pdf)'" plot_multiple.plg

%P1.pdf: %P1.tex img
	pdflatex $<

clean:
	$(RM) img$(BAR)* *.snm *.log *.toc *.aux *.nav *.out *P1.pdf

mrproper: clean
	$(RM) dats$(BAR)*
