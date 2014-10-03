import sys

def main(argv):
    import os
    
    if argv == []:
        repeticiones = 128
    else:
        repeticiones = int(argv[0])    

    if not repeticiones:
        repeticiones = 128

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
            #construirMinus1Input(n)

            bashCommand = " ./tp1ej3 -p recursos/testComplex.dat"
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

        s = open('recursos/graficarPromedio.dat', 'a+')
        s.write(str(n)+"   "+str(promedio)+"   "+str(repeticiones)+'\n')
        s.close()

        n += 1


def construirRandomInput(n):
    from random import randint
    s = open('recursos/testComplex.dat', 'wb+')
    s.write(str(n)+' '+str(randint(0,1000))+'\n')

    for i in range (0, n-1):
        for j in range (i+1, n):
            s.write(str(randint(0,100))+' ')
        s.write('\n')
    s.write('0')
    s.close()


def construirMinus1Input(n):
    s = open('recursos/testComplex.dat', 'wb+')
    s.write(str(n)+'1'+'\n')

    for i in range (0, n-1):
        for j in range (i+1, n):
            s.write('0 ')
        s.write('\n')
    s.write('0')
    s.close()

if __name__=="__main__":main(sys.argv[1:])
