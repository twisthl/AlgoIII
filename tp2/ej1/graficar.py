import sys

def main(argv):
    import os
    
    if argv == []:
        repeticiones = 300
    else:
        repeticiones = int(argv[0])    

    if not repeticiones:
        repeticiones = 300

    f = open('recursos/testComplex.dat', 'wb+')
    f.write(str(0))
    f.close()

    s = open('recursos/graficarPromedio.dat', 'wb+')
    s.close()

    n=1
    while (n <= 200000):
        
        f = open('recursos/times', 'wb+')
        f.close()
        
        for i in range(0,repeticiones):
            construirRandomInput(n)

            bashCommand = " ./tp2ej1 -p recursos/testComplex.in"
            os.system(bashCommand)

        f = open('recursos/times', 'r')
        suma = 0
        cant = 0
        for linea in f:
           suma += + float(linea)
           cant += 1
        f.close()

        promedio = suma / cant
        print (promedio)

        if (promedio*repeticiones > 20 and repeticiones != 1):
            repeticiones = repeticiones/4

        s = open('recursos/resultadosNVariado.dat', 'a+')
        s.write(str(n)+"   "+str(promedio)+"   "+str(repeticiones)+'\n')
        s.close()

        n += 1


def construirRandomInput(n):
    from random import randint
    s = open('recursos/testComplex.in', 'wb+')

    m = randint(2,2*n)

    s.write('0 1 '+ str(n) + '\n')
    for i in range (0, n):
        origen = randint(0, m)
        destino = randint(0, m)
        inicio = randint(0, n)*4
        fin = inicio + randint(1, 10)
        if (origen == destino):
            destino += 1
        s.write(str(origen)+' '+str(destino)+' '+str(inicio)+' '+str(fin)+'\n')
    s.close()

if __name__=="__main__":main(sys.argv[1:])
