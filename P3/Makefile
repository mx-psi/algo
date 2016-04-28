CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard cpps/*.cpp)

ifdef SystemRoot  # Windows
	RM = del /q
	SCRIPT = script.bat
	BAR = \\
else
	SCRIPT = ./script.sh
	BAR = /
endif

all: PresentacionP1.pdf MemoriaP1.pdf
.PHONY: all clean mrproper
.PRECIOUS: $(DATS) $(IMGS)

exes: $(CPPS:cpps/%.cpp=%.exe)
%.exe: cpps/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Nota: requiere cambiar la salida de tsp.exe para funcionar
%_tsp.pdf: datosTSP/%.tsp datosTSP/%.opt.tour tsp.exe tsp_coord.exe
	.$(BAR)tsp $< 1 > resultadosTSP$(BAR)$(@:_tsp.pdf=_1.tour)
	.$(BAR)tsp $< 2 > resultadosTSP$(BAR)$(@:_tsp.pdf=_2.tour)
	.$(BAR)tsp $< 3 > resultadosTSP$(BAR)$(@:_tsp.pdf=_3.tour)
	.$(BAR)tsp_coord $< $(@:_tsp.pdf=_1.tour) > resultadosTSP$(BAR)$(@:_tsp.pdf=_1.dat)
	.$(BAR)tsp_coord $< $(@:_tsp.pdf=_2.tour) > resultadosTSP$(BAR)$(@:_tsp.pdf=_2.dat)
	.$(BAR)tsp_coord $< $(@:_tsp.pdf=_3.tour) > resultadosTSP$(BAR)$(@:_tsp.pdf=_3.dat)
	.$(BAR)tsp_coord $< $(word 2, $^) > resultadosTSP$(BAR)$(@:_tsp.pdf=_opt.dat)
	gnuplot -e "OUT='$(@:.pdf=_1.pdf)'; TITLE='ASDF'; LEGEND='JKLM'; DATA='resultadosTSP$(BAR)$(@:_tsp.pdf=_1.dat)'" plotTSP.plg
	gnuplot -e "OUT='$(@:.pdf=_2.pdf)'; TITLE='ASDF'; LEGEND='JKLM'; DATA='resultadosTSP$(BAR)$(@:_tsp.pdf=_2.dat)'" plotTSP.plg
	gnuplot -e "OUT='$(@:.pdf=_3.pdf)'; TITLE='ASDF'; LEGEND='JKLM'; DATA='resultadosTSP$(BAR)$(@:_tsp.pdf=_3.dat)'" plotTSP.plg
	gnuplot -e "OUT='$(@:.pdf=_opt.pdf)'; TITLE='ASDF'; LEGEND='JKLM'; DATA='resultadosTSP$(BAR)$(@:_tsp.pdf=_opt.dat)'" plotTSP.plg

%P2.pdf: %P2.tex
	pdflatex $<
	pdflatex $<

clean:
	$(RM) *.snm *.log *.toc *.aux *.nav *.out *P2.pdf

mrproper: clean
	$(RM) dats$(BAR)* img$(BAR)*
