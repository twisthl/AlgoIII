set out "../informe/imagenes/ej1_chartComplejidad.png"
set xlabel "Cantidad de vuelos (Total)"
set ylabel "Tiempo (seg)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
plot "recursos/resultadosNVariado.dat" title "Complejidad practica", 0.000000014*x*x title "O(n^2)"