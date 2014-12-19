set out "../../informe/img/greedyN1.png"
set xlabel "Cantidad de nodos"
set ylabel "Tiempo (segundos)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,14"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
plot "resultados/resultadosNVariadoK2M15.dat" title "Densidad = 15%", "resultados/resultadosNVariadoK2M50.dat" title "Densidad = 50%", "resultados/resultadosNVariadoK2M100.dat" title "Densidad = 100% (grafos completos)", 0.00000009*x*x title "O(n^2) * 15%", 0.00000025*x*x title "O(n^2) * 50%", 0.00000052*x*x title "O(n^2) * 100%"