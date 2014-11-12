set out "../informe/imagenes/ej2_chartRendimiento3.png"
set xlabel "N=K"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y

plot "tiemposKN100.out" title "Datos con N igual a K", 29*x*x*x title "O(n)"
