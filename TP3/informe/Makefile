SHELL=/bin/bash -O extglob
#PREF=ej_1_2
PREF2=tp3_informe

OBJ=$(PREF).tex


tp1_informe.pdf: $(PREF2).tex
	pdflatex $(PREF2).tex

ej1_1_2.pdf: $(OBJ)
	pdflatex $(OBJ)

clean:
	rm !(*tex|Makefile|*jpg|*sty)

