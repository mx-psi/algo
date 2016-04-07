CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard cpps/*.cpp)
DATS = $(CPPS:cpps/%.cpp=dats/%.dat)
IND = $(CPPS:cpps/%.cpp=img/%_g.pdf)
TODOS = $(patsubst dats/%_inaki.dat, img/%_todos_g.pdf, $(wildcard dats/*_inaki.dat))

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
.PRECIOUS: $(DATS) $(IMGS)

exes: $(CPPS:cpps/%.cpp=%.exe)
%.exe: cpps/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

img/%_g.pdf: dats/%.dat
	gnuplot -e "DATA='$<';OUT='$@';TITLE='Tiempos de ejecución \
	de $(notdir $(basename $^))'; LEGEND='$(notdir $(basename $^))'" plot.plg

img/%_todos_g.pdf: dats/%_antonio.dat dats/%_dario.dat dats/%_inaki.dat dats/%_jose_manuel.dat dats/%_pablo.dat
	gnuplot -e "DATA='$(notdir $(basename $^))';OUT='$@';\
	TITLE='Tiempos de ejecución para $(patsubst img/%_todos_g.pdf, %, $@)'" plot_multiple.plg

%P2.pdf: %P2.tex
	pdflatex $<
	pdflatex $<

clean:
	$(RM) *.snm *.log *.toc *.aux *.nav *.out *P2.pdf

mrproper: clean
	$(RM) dats$(BAR)* img$(BAR)*
