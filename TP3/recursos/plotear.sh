#!/bin/bash

for dir in "receive_con_delay" "receive_sin_delay"
do
    beta=0.25
    for proba in {0..50..25}; do
	for delay in {100..400..100}; do
	    bsalida="../graphs/${dir}/beta.0.25.delay.${delay}.proba.${proba}.png"
	    btitulo="beta standar, alfa variable, delay ${delay} probabilidad de pérdida ${proba}%"
	    barch1="../data/${dir}/alfa.0.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    barch2="../data/${dir}/alfa.0.25.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    barch3="../data/${dir}/alfa.0.5.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    barch4="../data/${dir}/alfa.1.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    barch5="../data/${dir}/alfa.0.125.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    betiqueta1="rto/rtt alfa 0"
	    betiqueta2="rto/rtt alfa 0.25"
	    betiqueta3="rto/rtt alfa 0.5"
	    betiqueta4="rto/rtt alfa 1"
	    betiqueta5="rto/rtt alfa standar"
	    gnuplot -e "salida='${bsalida}'; titulo='${btitulo}'; arch1='${barch1}'; arch2='${barch2}'; arch3='${barch3}'; arch4='${barch4}'; arch5='${barch5}'; etiqueta1='${betiqueta1}'; etiqueta2='${betiqueta2}'; etiqueta3='${betiqueta3}'; etiqueta4='${betiqueta4}'; etiqueta5='${betiqueta5}'" gnu2.plot
	done
    done

    for proba in {0..50..25}; do
	for delay in {100..400..100}; do
	    bsalida="../graphs/${dir}/alfa.0.125.delay.${delay}.proba.${proba}.png"
	    btitulo="alfa standar, beta variable, delay ${delay} probabilidad de pérdida ${proba}%"
	    barch1="../data/${dir}/alfa.0.125.beta.0.delay.${delay}.proba.${proba}.dat"
	    barch2="../data/${dir}/alfa.0.125.beta.0.50.delay.${delay}.proba.${proba}.dat"
	    barch3="../data/${dir}/alfa.0.125.beta.0.75.delay.${delay}.proba.${proba}.dat"
	    barch4="../data/${dir}/alfa.0.125.beta.1.delay.${delay}.proba.${proba}.dat"
	    barch5="../data/${dir}/alfa.0.125.beta.0.25.delay.${delay}.proba.${proba}.dat"
	    betiqueta1="rto/rtt beta 0" 
	    betiqueta2="rto/rtt beta 0.50" 
	    betiqueta3="rto/rtt beta 0.75" 
	    betiqueta4="rto/rtt beta 1" 
	    betiqueta5="rto/rtt beta standar"
	    echo $bsalida
	    gnuplot -e "salida='${bsalida}'; titulo='${btitulo}'; arch1='${barch1}'; arch2='${barch2}'; arch3='${barch3}'; arch4='${barch4}'; arch5='${barch5}'; etiqueta1='${betiqueta1}'; etiqueta2='${betiqueta2}'; etiqueta3='${betiqueta3}'; etiqueta4='${betiqueta4}'; etiqueta5='${betiqueta5}'" gnu2.plot
	done
    done
done