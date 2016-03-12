CXX = g++
CPPFLAGS = -std=gnu++0x

CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
PNGS = $(CPPS:.cpp=.png)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat	

else
	RM = rm
	SCRIPT = ./script.sh
	SCRIPT_PLOT_CONFIG = ./script_plot_config.sh
	SCRIPT_GNUPLOT = ./script_gnuplot.sh
endif

.PRECIOUS: $(DATS) $(PNGS)

%.exe: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.exe
	$(SCRIPT) $< 1 1 25

%.png: %.dat
	$(SCRIPT_PLOT_CONFIG) $< "Capacidad del vector" "Tiempos de ejecución" "Tiempos de ejecución de burbuja" $<
	$(SCRIPT_GNUPLOT) $< $@

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	$(RM) *.png *.dat *.exe *.snm *.log *.toc *.aux *.nav
