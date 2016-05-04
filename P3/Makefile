CXXFLAGS = -std=gnu++0x
CPPS = $(wildcard cpps/*.cpp)
TSPS = $(wildcard datosTSP/*.tsp)
TOURS = $(TSPS:datosTSP/%.tsp=resultadosTSP/%_1.tour) $(TSPS:datosTSP/%.tsp=resultadosTSP/%_2.tour) $(TSPS:datosTSP/%.tsp=resultadosTSP/%_3.tour)
DATS = $(TSPS:datosTSP/%.tsp=resultadosTSP/%_1.dat) $(TSPS:datosTSP/%.tsp=resultadosTSP/%_2.dat) $(TSPS:datosTSP/%.tsp=resultadosTSP/%_3.dat) $(TSPS:datosTSP/%.tsp=resultadosTSP/%_opt.dat)

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
.PRECIOUS: $(TOURS) $(DATS) $(IMGS)

exes: $(CPPS:cpps/%.cpp=%.exe)
%.exe: cpps/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

resultadosTSP/%_1.tour: datosTSP/%.tsp tsp.exe
	.$(BAR)tsp $< 1

resultadosTSP/%_2.tour: datosTSP/%.tsp tsp.exe
	.$(BAR)tsp $< 2

resultadosTSP/%_3.tour: datosTSP/%.tsp tsp.exe
	.$(BAR)tsp $< 3

resultadosTSP/%_opt.dat: datosTSP/%.tsp datosTSP/%.opt.tour tsp_coord.exe
	.$(BAR)tsp_coord $< $(word 2, $^) > $@

resultadosTSP/%_1.dat: datosTSP/%.tsp resultadosTSP/%_1.tour tsp_coord.exe
	.$(BAR)tsp_coord $< $(word 2, $^) > $@

resultadosTSP/%_2.dat: datosTSP/%.tsp resultadosTSP/%_2.tour tsp_coord.exe
	.$(BAR)tsp_coord $< $(word 2, $^) > $@

resultadosTSP/%_3.dat: datosTSP/%.tsp resultadosTSP/%_3.tour tsp_coord.exe
	.$(BAR)tsp_coord $< $(word 2, $^) > $@

%_tsp.pdf: resultadosTSP/%_1.dat resultadosTSP/%_2.dat resultadosTSP/%_3.dat resultadosTSP/%_opt.dat
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
