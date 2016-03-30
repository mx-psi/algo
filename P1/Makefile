CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard cpps/*.cpp)
DATS = $(CPPS:cpps/%.cpp=dats/%.dat)
IND = $(CPPS:cpps/%.cpp=img/%_g.pdf)
TODOS = $(patsubst dats/%_inaki.dat, img/%_todos_g.pdf, $(wildcard dats/*_inaki.dat))
IMGS = $(IND) $(TODOS) img/comparativa_global_g.pdf img/comparativa_logaritmicos_g.pdf img/comparativa_cuadraticos_g.pdf

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat
	BAR = \\
	CXXFLAGS := $(CXXFLAGS) -Dsrandom=srand -Drandom()="(rand()<<16)|(rand()<<1)|(rand()&1)"
else
	SCRIPT = ./script.sh
	BAR = /
endif

all: PresentacionP1.pdf MemoriaP1.pdf
.PHONY: img all clean mrproper
.PRECIOUS: $(DATS) $(IMGS)

exes: $(CPPS:cpps/%.cpp=%.exe)
%.exe: cpps/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

img/comparativa_cuadraticos_g.pdf: dats/burbuja.dat dats/seleccion.dat dats/insercion.dat
	gnuplot -e "DATA='$(notdir $(basename $^))';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos cuadráticos'" plot_multiple.plg

img/comparativa_logaritmicos_g.pdf: dats/quicksort.dat dats/heapsort.dat dats/mergesort.dat
	gnuplot -e "DATA='$(notdir $(basename $^))';OUT='$@';\
	TITLE='Tiempos de ejecución para algoritmos n·log(n)'" plot_multiple.plg

img/comparativa_global_g.pdf: dats/quicksort.dat dats/heapsort.dat dats/mergesort.dat dats/burbuja.dat dats/seleccion.dat dats/insercion.dat
	gnuplot -e "DATA='$(notdir $(basename $^))';OUT='$@';\
	TITLE='Tiempos de ejecución de globales'" plot_multiple.plg

img/%_g.pdf: dats/%.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución \
	de $(notdir $(basename $^))'; LEGEND='$(notdir $(basename $^))'" plot.plg

img/%_todos_g.pdf: dats/%_antonio.dat dats/%_dario.dat dats/%_inaki.dat dats/%_jose_manuel.dat dats/%_pablo.dat
	gnuplot -e "DATA='$(notdir $(basename $^))';OUT='$@';\
	TITLE='Tiempos de ejecución para $(notdir $(basename $@ _todos_g.pdf))'" plot_multiple.plg

tablas:
	ruby tablas_gen.rb

%P1.pdf: %P1.tex $(GPHS) $(IMGS) #tablas
	pdflatex $<
	pdflatex $<

clean:
	$(RM) *.snm *.log *.toc *.aux *.nav *.out *P1.pdf

mrproper: clean
	$(RM) dats$(BAR)* img$(BAR)*
