import sys

def main(argv):
    import os
    construirComparaciones()


def construirComparaciones():
    import os
    from random import randint

    for n in range(5,20):
        for k in range(2, 8):
            m = int(((n * (n-1))/2)*0.15)

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP', 'wb+')
            f.close()


            for q in range(0,10):
                nombre = 'N' + str(n) + 'K' + str(k) + 'M15COMPARACION.grafo'
                s = open(str('../recursos/comparando/' + nombre), 'wb+')
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

                bashCommand = " ./algo3tp3 -EX -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -p ../recursos/comparando/" + nombre
                os.system(bashCommand)


            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            r = open('../recursos/comparando/GREED', 'r')
            lineasGE = r.readlines()
            r.close()
            s = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBU = s.readlines()
            s.close()
            t = open('../recursos/comparando/GRASP', 'r')
            lineasGR = t.readlines()
            t.close()

            promedioGE = 0
            promedioBU = 0
            promedioGR = 0
            for z in range(0,len(lineasEX)):
                promedioGE += (float(lineasEX[k]) + 1)/(float(lineasGE[k]) + 1)
                promedioBU += (float(lineasEX[k]) + 1)/(float(lineasBU[k]) + 1)
                promedioGR += (float(lineasEX[k]) + 1)/(float(lineasGR[k]) + 1)

            promedioGE = promedioGE/len(lineasEX)
            promedioBU = promedioBU/len(lineasEX)
            promedioGR = promedioGR/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGE)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBU)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASPK' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGR)+'\n')
            s.close()


            m = int(((n * (n-1))/2)/2)

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP', 'wb+')
            f.close()


            for q in range(0,10):
                nombre = 'N' + str(n) + 'K' + str(k) + 'M50COMPARACION.grafo'
                s = open(str('../recursos/comparando/' + nombre), 'wb+')
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

                bashCommand = " ./algo3tp3 -EX -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -p ../recursos/comparando/" + nombre
                os.system(bashCommand)


            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            r = open('../recursos/comparando/GREED', 'r')
            lineasGE = r.readlines()
            r.close()
            s = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBU = s.readlines()
            s.close()
            t = open('../recursos/comparando/GRASP', 'r')
            lineasGR = t.readlines()
            t.close()

            promedioGE = 0
            promedioBU = 0
            promedioGR = 0
            for z in range(0,len(lineasEX)):
                promedioGE += (float(lineasEX[k]) + 1)/(float(lineasGE[k]) + 1)
                promedioBU += (float(lineasEX[k]) + 1)/(float(lineasBU[k]) + 1)
                promedioGR += (float(lineasEX[k]) + 1)/(float(lineasGR[k]) + 1)

            promedioGE = promedioGE/len(lineasEX)
            promedioBU = promedioBU/len(lineasEX)
            promedioGR = promedioGR/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGE)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M50OMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBU)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASPK' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGR)+'\n')
            s.close()


            m = (n * (n-1))/2

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP', 'wb+')
            f.close()


            for q in range(0,10):
                nombre = 'N' + str(n) + 'K' + str(k) + 'M100COMPARACION.grafo'

                r = open(str('../recursos/comparando/' + nombre), 'wb+')

                r.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')

                for i in range(1, (n)):
                    for j in range((i+1), (n+1)):
                        w = randint(1, 999)
                        r.write(str(i) + ' ' + str(j) + ' ' + str(w) + '\n')
                r.close()
                bashCommand = " ./algo3tp3 -EX -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            r = open('../recursos/comparando/GREED', 'r')
            lineasGE = r.readlines()
            r.close()
            s = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBU = s.readlines()
            s.close()
            t = open('../recursos/comparando/GRASP', 'r')
            lineasGR = t.readlines()
            t.close()

            promedioGE = 0
            promedioBU = 0
            promedioGR = 0
            for z in range(0,len(lineasEX)):
                promedioGE += (float(lineasEX[k]) + 1)/(float(lineasGE[k]) + 1)
                promedioBU += (float(lineasEX[k]) + 1)/(float(lineasBU[k]) + 1)
                promedioGR += (float(lineasEX[k]) + 1)/(float(lineasGR[k]) + 1)
            promedioGE = promedioGE/len(lineasEX)
            promedioBU = promedioBU/len(lineasEX)
            promedioGR = promedioGR/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGE)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBU)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASPK' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGR)+'\n')
            s.close()



if __name__=="__main__":main(sys.argv[1:])