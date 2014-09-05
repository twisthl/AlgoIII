set out "../informe/imagenes/ej1_testSaltoMaximo.png"
set xlabel "Salto Maximo"
set ylabel "Tiempo (clocks)"
set key left top
set terminal png size 1300,800 enhanced font "Helvetica,20"
#set xrange [0:1e+06]
#set yrange [0:1e+06]
#set logscale y
plot "resultados/saltoMax/7082446.out" title "#tablones = 7082446", "resultados/saltoMax/20540202.out" title "#tablones = 20540202", "resultados/saltoMax/22861456.out" title "#tablones = 22861456", "resultados/saltoMax/29069981.out" title "#tablones = 29069981", "resultados/saltoMax/38496567.out" title "#tablones = 38496567", "resultados/saltoMax/48263302.out" title "#tablones = 48263302", "resultados/saltoMax/75501740.out" title "#tablones = 75501740", "resultados/saltoMax/89789692.out" title "#tablones = 89789692", "resultados/saltoMax/92472396.out" title "#tablones = 92472396", "resultados/saltoMax/99766165.out" title "#tablones = 99766165"