set out "../informe/imagenes/ej2_chartRendimiento.png"
set xlabel "Cantidad de Edificios (Total)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
plot "tiemposEdificios.out" title "0.38 * Datos aleatorios (seed 1)", x title "O(n)", 0.38*x*log(x)/log(2) title "O(n log(n))"
