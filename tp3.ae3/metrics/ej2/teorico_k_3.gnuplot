set terminal png size 800,600
set output "teorico_k_3.png"

set ylabel "Tiempo de ejecucion"
set xlabel "Nodos"
set logscale y
set title ''
plot 'teorico' pt 5 ps 1.5 title "k! * k^(n-k)", \
     'backtrack_times/ej2_metrics_backtrack_time_k:3_d:0.80' pt 6 ps 1.5 title "k=3, densidad=0.80"
