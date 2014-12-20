#!/bin/bash

for particiones in {2..3}; do
	for aristas in {15,50,100}; do
	    bsalida="../informe/img/ComparacionesCon${particiones}Particiones${aristas}Aristas.png"
	    btitulo="Comparacion del Algoritmo Exacto contra las Heuristicas con ${aristas}% de Aristas y ${particiones} Particiones"
	    barch1="./comparando/BUSQUEDAK${particiones}M${aristas}COMPARACION.dat"
	    barch2="./comparando/GREEDK${particiones}M${aristas}COMPARACION.dat"
	    barch3="./comparando/GRASPK${particiones}M${aristas}COMPARACION.dat"
	    betiqueta1="Busqueda Local"
	    betiqueta2="Greedy"
	    betiqueta3="GRASP"
	    gnuplot -e "salida='${bsalida}'; titulo='${btitulo}'; arch1='${barch1}'; arch2='${barch2}'; arch3='${barch3}'; etiqueta1='${betiqueta1}'; etiqueta2='${betiqueta2}'; etiqueta3='${betiqueta3}'" gnucomparaciones.plot
	done
done