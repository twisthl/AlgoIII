set out "../informe/imagenes/ej3_chartComplejidad.png"
set xlabel "Cantidad de Quimicos (Total)"
set ylabel "Tiempo (seg)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
set logscale y
plot "recursos/promSinPoda.dat" title "Algoritmo sin poda", "recursos/complejidadBell.dat" title "Complejidad teorica"