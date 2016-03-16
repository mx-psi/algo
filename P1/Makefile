CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
GPHS = $(CPPS:.cpp=_g.pdf)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat
else
	SCRIPT = ./script.sh
endif

all: PresentacionP1.pdf MemoriaP1.pdf

.PRECIOUS: $(DATS) $(GPHS)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.dat: %.exe
	$(SCRIPT) $< 2000 2000 50000

comparativa_cuadraticos_g.pdf: burbuja.dat seleccion.dat insercion.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos cuadráticos'" plot_multiple.plg

comparativa_logaritmicos_g.pdf: quicksort.dat heapsort.dat mergesort.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos n·log(n)'" plot_multiple.plg

comparativa_global_g.pdf: quicksort.dat heapsort.dat mergesort.dat burbuja.dat seleccion.dat insercion.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución de globales'" gnuplot_script_cuad

%_g.pdf: %.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución \
	de $(basename $< .dat)'; LEGEND='$(basename $< .dat)'" plot.plg

%P1.pdf: %P1.tex $(GPHS)
	pdflatex $<

img: $(GPHS)

clean:
	$(RM) *_g.pdf *.exe *.snm *.log *.toc *.aux *.nav *.out *P1.pdf

mrproper: clean
	$(RM) *.dat
