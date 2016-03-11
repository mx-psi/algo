CXX = g++
CPPFLAGS = -std=gnu++0x

CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
PNGS = $(CPPS:.cpp=.png)

.PRECIOUS: $(DATS) $(PNGS)

%.exe: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.exe
	./script.sh $< 1 1 25

%.png: %.dat
	gnuplot -e "data='$<'" -e "out='$@'" plot.plg

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	rm *.png *.dat *.out *.snm *.log *.toc *.aux *.nav
