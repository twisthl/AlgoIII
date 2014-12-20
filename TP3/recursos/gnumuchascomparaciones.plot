set terminal png size 1366, 768

set xlabel "Cantidad de nodos"
set ylabel "Divergencia contra GRASO con 40 iteraciones"

print "------------------------------gnuplot--------------------------------"
print "              ...............ploteando.............."
 print "salida"
 print salida
 print "titulo"
 print titulo
# print "arch1"
# print arch1
# print "arch2"
# print arch2
# print "arch3"
# print arch3
# print "arch4"
# print arch4
# print "etiqueta1"
# print etiqueta1
# print "etiqueta2"
# print etiqueta2
# print "etiqueta3"
# print etiqueta3
# print "etiqueta4"
# print etiqueta4
# print "etiqueta5"
# print etiqueta5

set output salida 
set title titulo 

plot arch1 using 1:2 with lines linewidth 2 title etiqueta1 ,\
     arch2 using 1:2 with lines linewidth 2 title etiqueta2 ,\
     arch3 using 1:2 with lines linewidth 2 title etiqueta3 ,\
	 arch4 using 1:2 with lines linewidth 2 title etiqueta4