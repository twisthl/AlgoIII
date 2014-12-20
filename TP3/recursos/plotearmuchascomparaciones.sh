#!/bin/bash

for particiones in {5,30,70}; do
	for aristas in {15,50,100}; do
	    bsalida="../informe/img/muchosComparacionesCon${particiones}Particiones${aristas}Aristas.png"
	    btitulo="Comparacion de las Heuristicas contra GRASP40 con ${aristas}% de Aristas y ${particiones} Particiones"
	    barch1="./comparando/BUSQUEDAK${particiones}M${aristas}NGRANDECOMPARACION.dat"
	    barch2="./comparando/GREEDK${particiones}M${aristas}NGRANDECOMPARACION.dat"
	    barch3="./comparando/GRASP5K${particiones}M${aristas}NGRANDECOMPARACION.dat"
	    barch4="./comparando/GRASP15K${particiones}M${aristas}NGRANDECOMPARACION.dat"
#	    barch5="./comparando/GRASP40K${particiones}M${aristas}NGRANDECOMPARACION.dat"
	    betiqueta1="Busqueda Local"
	    betiqueta2="Greedy"
	    betiqueta3="GRASP5"
	    betiqueta4="GRASP15"
	    betiqueta5="GRASP40"
	    gnuplot -e "salida='${bsalida}'; titulo='${btitulo}'; arch1='${barch1}'; arch2='${barch2}'; arch3='${barch3}'; arch4='${barch4}'; etiqueta1='${betiqueta1}'; etiqueta2='${betiqueta2}'; etiqueta3='${betiqueta3}'; etiqueta4='${betiqueta4}'" gnumuchascomparaciones.plot
	done
done