set terminal png size 800,600
set output "k_4.png"

set ylabel "Tiempo de ejecucion"
set xlabel "Nodos"
set title 'Tiempos con k=4 y distintas densidades'
set logscale y
plot 'backtrack_times/ej2_metrics_backtrack_time_k:4_d:0.20' pt 5 ps 1.5 title "k=4, densidad=0.20", \
     'backtrack_times/ej2_metrics_backtrack_time_k:4_d:0.5'  pt 6 ps 1.5 title "k=4, dendidad=0.50", \
     'backtrack_times/ej2_metrics_backtrack_time_k:4_d:0.80' pt 4 ps 1.5 title "k=4, densidad=0.80"
