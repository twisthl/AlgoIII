import sys

def main(argv):
    import os
    
#    tiempos()

    construirRandomInput()


def construirRandomInput():
    import os
    from random import randint

    for n in range(15,20):
        for k in range(2, 8):
            m = int(((n * (n-1))/2)*0.15)
            
            f = open('../recursos/times', 'wb+')
            f.close()

#            for q in range(0,5):
            nombre = 'N' + str(n) + 'K' + str(k) + 'M15SINPODA.grafo'
            s = open(str('../recursos/instancias/' + nombre), 'wb+')
            s.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')
            aristas = {}
            for i in range(0, m):
                origen = randint(1, (n-1))
                destino = randint(2,n)
                while (destino<=origen):
                    destino = randint(2,n)
                while ((str(str(origen)+str(destino))) in aristas):
                    origen = randint(1, (n-1))
                    destino = randint(2,n)
                    while (destino<=origen):
                        destino = randint(2,n)
                aristas[str(str(origen)+str(destino))] = 1
                w = randint(1, 999)
                s.write(str(origen) + ' ' + str(destino) + ' '+ str(w) + '\n')
            s.close()

            bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + nombre
            os.system(bashCommand)

            r = open('../recursos/times', 'r')
            suma = 0
            cant = 0
            for linea in r:
               suma += + float(linea)
               cant += 1
            r.close()

            promedio = suma / cant
            print (promedio)

            s = open('../recursos/resultadosNVariadoK' + str(k) + 'M15SINPODA.dat', 'a+')
            s.write(str(n)+"   "+str(promedio)+'\n')
            s.close()


            m = int(((n * (n-1))/2)/2)
            f = open('../recursos/times', 'wb+')
            f.close()
#            for q in range(0,5):
            nombre = 'N' + str(n) + 'K' + str(k) + 'M50SINPODA.grafo'
            t = open(str('../recursos/instancias/' + nombre), 'wb+')
            t.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')
            aristas = {}
            for i in range(0, m):
                
                origen = randint(1, (n-1))
                destino = randint(2,n)
                while (destino<=origen):
                    destino = randint(2,n)

                while ((str(str(origen)+str(destino))) in aristas):
                    origen = randint(1, (n-1))
                    destino = randint(2,n)
                    while (destino<=origen):
                        destino = randint(2,n)

                aristas[str(str(origen)+str(destino))] = 1

                w = randint(1, 999)

                t.write(str(origen) + ' ' + str(destino) + ' '+ str(w) + '\n')
            t.close()

            bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + nombre
            os.system(bashCommand)

            r = open('../recursos/times', 'r')
            suma = 0
            cant = 0
            for linea in r:
               suma += + float(linea)
               cant += 1
            r.close()

            promedio = suma / cant
            print (promedio)

            s = open('../recursos/resultadosNVariadoK' + str(k) + 'M50SINPODA.dat', 'a+')
            s.write(str(n)+"   "+str(promedio)+'\n')
            s.close()

            m = (n * (n-1))/2
            f = open('../recursos/times', 'wb+')
            f.close()
#            for q in range(0,5):
            nombre = 'N' + str(n) + 'K' + str(k) + 'M100SINPODA.grafo'

            r = open(str('../recursos/instancias/' + nombre), 'wb+')

            r.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')

            for i in range(1, (n)):
                for j in range((i+1), (n+1)):
                    w = randint(1, 999)
                    r.write(str(i) + ' ' + str(j) + ' ' + str(w) + '\n')
            r.close()
            bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + nombre
            os.system(bashCommand)

            r = open('../recursos/times', 'r')
            suma = 0
            cant = 0
            for linea in r:
               suma += + float(linea)
               cant += 1
            r.close()

            promedio = suma / cant
            print (promedio)

            s = open('../recursos/resultadosNVariadoK' + str(k) + 'M100SINPODA.dat', 'a+')
            s.write(str(n)+"   "+str(promedio)+'\n')
            s.close()

def tiempos():
        import os

        for k in range(2, 8):
            for n in range(5,20):
                instancia = 'N' + str(n) + 'K' + str(k) + 'M15SINPODA.grafo'
                
                f = open('../recursos/times', 'wb+')
                f.close()

                for i in range(0,30):
                    bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + instancia
                    os.system(bashCommand)

                r = open('../recursos/times', 'r')
                suma = 0
                cant = 0
                for linea in r:
                   suma += + float(linea)
                   cant += 1
                r.close()

                promedio = suma / cant
                print (promedio)

                s = open('../recursos/resultadosNVariadoK' + str(k) + 'M15SINPODA.dat', 'a+')
                s.write(str(n)+"   "+str(promedio)+'\n')
                s.close()

                instancia = 'N' + str(n) + 'K' + str(k) + 'M50SINPODA.grafo'
                
                f = open('../recursos/times', 'wb+')
                f.close()

                for i in range(0,30):
                    bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + instancia
                    os.system(bashCommand)

                r = open('../recursos/times', 'r')
                suma = 0
                cant = 0
                for linea in r:
                   suma += + float(linea)
                   cant += 1
                r.close()

                promedio = suma / cant
                print (promedio)

                s = open('../recursos/resultadosNVariadoK' + str(k) + 'M50SINPODA.dat', 'a+')
                s.write(str(n)+"   "+str(promedio)+'\n')
                s.close()

                instancia = 'N' + str(n) + 'K' + str(k) + 'M100SINPODA.grafo'
                
                f = open('../recursos/times', 'wb+')
                f.close()

                for i in range(0,30):
                    bashCommand = " ./algo3tp3 -EX -p ../recursos/instancias/" + instancia
                    os.system(bashCommand)

                r = open('../recursos/times', 'r')
                suma = 0
                cant = 0
                for linea in r:
                   suma += + float(linea)
                   cant += 1
                r.close()

                promedio = suma / cant
                print (promedio)

                s = open('../recursos/resultadosNVariadoK' + str(k) + 'M100SINPODA.dat', 'a+')
                s.write(str(n)+"   "+str(promedio)+'\n')
                s.close()

if __name__=="__main__":main(sys.argv[1:])