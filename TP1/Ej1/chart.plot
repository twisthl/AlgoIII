set out "../informe/imagenes/ej1_chartRendimiento.png"
set xlabel "Cantidad de Tablones (Total)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
plot "resultados/tiempos.out" title "Datos aleatorios (seed 1)", "resultados/tiempos2.out" title "Datos aleatorios (seed 2)", "resultados/tiempos3.out" title "Datos aleatorios (seed 3)", 0.017*x title "O(n)"
