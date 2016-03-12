CXX = g++
CPPFLAGS = -std=gnu++0x

CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
PNGS = $(CPPS:.cpp=.png)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat	
	SCRIPT_PLOT_CONFIG = script_plot_config.bat
else
	RM = rm
	SCRIPT = ./script.sh
	SCRIPT_PLOT_CONFIG = ./script_plot_config.sh
endif

.PRECIOUS: $(DATS) $(PNGS)

%.exe: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.exe
	$(SCRIPT) $< 1 1 25

plot_%.plg: %.dat
	$(SCRIPT_PLOT_CONFIG) $< "Tamaño" "Tiempo de ejecución" "Tiempos de ejecución de $(subst .dat,,$<)" $<

%.png: %.dat plot_%.plg
	gnuplot -e "data='$<'" -e "out='$@'" plot.plg $(word 2, $^)

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	$(RM) *.png *.dat *.exe *.snm *.log *.toc *.aux *.nav
