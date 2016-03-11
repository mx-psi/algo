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
endif

.PRECIOUS: $(DATS) $(PNGS)

%.exe: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.exe
	$(SCRIPT) $< 1 1 25

%.png: %.dat
	gnuplot -e "data='$<'" -e "out='$@'" plot.plg

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	$(RM) *.png *.dat *.exe *.snm *.log *.toc *.aux *.nav
