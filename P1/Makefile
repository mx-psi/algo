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
	$(SCRIPT) $< 1 1 25

n2_g.pdf: burbuja.dat seleccion.dat insercion.dat
	gnuplot -e "DATA='$(basename $^)';OUT='$@';\
	TITLE='Tiempos de ejecución de cuadráticos'" plot_multiple.plg

%_g.pdf: %.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución \
	de $(basename $< .dat)'; LEGEND='$(basename $< .dat)'" plot.plg

%P1.pdf: %P1.tex $(GPHS)
	pdflatex $<

clean:
	$(RM) *_g.pdf *.exe *.snm *.log *.toc *.aux *.nav *.out *P1.pdf

mrproper: clean
	$(RM) *.dat
