set out "../informe/imagenes/ej2_chartRendimiento.png"
set xlabel "Cantidad de Edificios (Total)"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y

Archivo = "tiemposEdificios.out"

f(x) = x*log(x)/log(2)

plot Archivo using 1:2 title "Curva empírica",\
	 0.20*x*log(x)/log(2) title "0.2 * O(n log(n))",\
	 0.16*x*log(x)/log(2) title "0.16 * O(n log(n))",\
	 Archivo using 1:(2/(f($1))) title "Razón entre ambas curvas, empirica / teorica",\
	 x title "O(n)"
	 



set out "../informe/imagenes/ej2_chartRendimiento2.png"
set ylabel "Tiempo empirico"
set xlabel "Tiempo teorico"

plot Archivo using (f($1)):2 title "Relación entre Empeírico y Teórico",\
	0.16*x title "0.16 * x"
