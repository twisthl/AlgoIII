set terminal png size 1366, 768

set output "../graphs/retransmission.vs.proba.png"

set xlabel "probabilidad"
set ylabel "retransmisiones"

set title "retransmisiones vs probabilidad de perdida de paquete"

plot "../data/retransmission.vs.proba" using 1:2 with lines linewidth 2 title "retransmisiones"
