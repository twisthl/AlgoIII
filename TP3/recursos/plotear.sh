#!/bin/bash

for dir in "receive_con_delay" "receive_sin_delay"
do
	for particiones in {2..7}; do
	    bsalida="../informe/img/rendimientoExactoSinPoda${particiones}Particiones.png"
	    btitulo="Rendimiento del Algoritmo Exacto sin Podas en Funcion de la Cantidad de Aristas con ${particiones} Particiones"
	    barch1="./resultadosNVariadoK${particiones}M15SINPODA.dat"
	    barch2="./resultadosNVariadoK${particiones}M50SINPODA.dat"
	    barch3="./resultadosNVariadoK${particiones}M100SINPODA.dat"
	    betiqueta1="#Aristas 15%"
	    betiqueta2="#Aristas 50%"
	    betiqueta3="Grafo Completo"
	    gnuplot -e "salida='${bsalida}'; titulo='${btitulo}'; arch1='${barch1}'; arch2='${barch2}'; arch3='${barch3}'; etiqueta1='${betiqueta1}'; etiqueta2='${betiqueta2}'; etiqueta3='${betiqueta3}'" gnu2.plot
    done
done