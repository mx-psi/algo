CXX = g++
CPPFLAGS = -std=gnu++0x

CPPS = $(wildcard *.cpp)
DATS = $(CPPS:.cpp=.dat)
PNGS = $(CPPS:.cpp=.png)

.PRECIOUS: $(DATS)

%.out: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

%.dat: %.out
	./script.sh $< 1 1 25

%.png: %.dat
	gnuplot -e "data='$<'" -e "out='$@'" plot.plg

%.pdf: %.tex $(PNGS)
	pdflatex $<

mrproper:
	rm *.png *.dat *.out
