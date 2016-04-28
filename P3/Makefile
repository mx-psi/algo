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

%P2.pdf: %P2.tex
	pdflatex $<
	pdflatex $<

clean:
	$(RM) *.snm *.log *.toc *.aux *.nav *.out *P2.pdf

mrproper: clean
	$(RM) dats$(BAR)* img$(BAR)*
