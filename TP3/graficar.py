import sys

def main(argv):
    import os
    
    construirRandomInput()


def construirRandomInput():
    from random import randint
    for k in range(2, 7):
        for n in range(5, 16):
            m = int(((n * (n-1))/2)*0.15)
            
            nombre = 'N' + str(n) + 'K' + str(k) + 'M15.grafo'

            s = open(str('recursos/' + nombre), 'wb+')

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

            m = int(((n * (n-1))/2)/2)
            nombre = 'N' + str(n) + 'K' + str(k) + 'M50.grafo'

            t = open(str('recursos/' + nombre), 'wb+')

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

            m = (n * (n-1))/2
            nombre = 'N' + str(n) + 'K' + str(k) + 'M100.grafo'

            r = open(str('recursos/' + nombre), 'wb+')

            r.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')

            for i in range(0, (n-1)):
                for j in range((i+1), n):
                    w = randint(1, 999)
                    r.write(str(i) + ' ' + str(j) + ' ' + str(w) + '\n')
            r.close()

if __name__=="__main__":main(sys.argv[1:])