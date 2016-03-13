CPPFLAGS = -std=gnu++0x
CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
PNGS = $(CPPS:.cpp=.png)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat
else
	SCRIPT = ./script.sh
endif

all: PresentacionP1.pdf MemoriaP1.pdf

.PRECIOUS: $(DATS) $(PNGS)

%.exe: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.exe
	$(SCRIPT) $< 1 1 25

%.png: %.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución de $(basename $< .dat)'; \
	LABELX='Tamaño'; LABELY='Tiempo de ejecución';LEGEND='$(basename $< .dat)'" plot.plg

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	$(RM) *.png *.dat *.exe *.snm *.log *.toc *.aux *.nav
