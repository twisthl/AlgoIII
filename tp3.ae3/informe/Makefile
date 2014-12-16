SHELL := /bin/bash -O extglob

.PHONY: all dot clean

PDF=informe.pdf
TEXFILES=
FIGS=$(addsuffix .tex, $(basename $(wildcard dot/*dot)))
EJs=ej1 ej2 ej3 ej4 ej5 ej6

all: $(PDF)

$(PDF): $(EJs) informe.tex
	pdflatex informe.tex
	pdflatex informe.tex
clean:
	rm -f $(PDF) *.aux *.log *.toc informe.out informe.blg informe.bbl

