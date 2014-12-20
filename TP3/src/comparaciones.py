import sys

def main(argv):
    import os
    construirComparaciones()


def construirComparaciones():
    import os
    from random import randint

    for k in range(2, 8):
        s = open('../recursos/comparando/GREEDK' + str(k) + 'M15COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M15COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP5K' + str(k) + 'M15COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP15K' + str(k) + 'M15COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP40K' + str(k) + 'M15COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GREEDK' + str(k) + 'M50COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M50COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP5K' + str(k) + 'M50COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP15K' + str(k) + 'M50COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP40K' + str(k) + 'M50COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GREEDK' + str(k) + 'M100COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M100COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP5K' + str(k) + 'M100COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP15K' + str(k) + 'M100COMPARACION.dat', 'wb+')
        s.close()
        s = open('../recursos/comparando/GRASP40K' + str(k) + 'M100COMPARACION.dat', 'wb+')
        s.close()

#    for k in range(2, 8):
    for n in range(5,100):
        for k in range(2, 8):
            
            if n> 16:
                v = 3
            else:
                v = 16

            m = int(((n * (n-1))/2)*0.15)

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP5', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP15', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP40', 'wb+')
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'wb+')
            f.close()


            for q in range(0,v):
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

                bashCommand = " ./algo3tp3 -EX -s -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 5 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 15 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 40 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -PS -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)


            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            f = open('../recursos/comparando/GREED', 'r')
            lineasGD = f.readlines()
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBL = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP5', 'r')
            lineasGP5 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP15', 'r')
            lineasGP15 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP40', 'r')
            lineasGP40 = f.readlines()
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'r')
            lineasPS = f.readlines()
            f.close()

            sumatoriaGD = 0
            sumatoriaBL = 0
            sumatoriaGP5 = 0
            sumatoriaGP15 = 0
            sumatoriaGP40 = 0
            for z in range(0,len(lineasEX)):
                if (float(lineasPS[z]) == float(lineasEX[z])):
                    calidadGD = 1
                    calidadBL = 1
                    calidadGP5 = 1
                    calidadGP15 = 1
                    calidadGP40 = 1
                else:
                    calidadGD = 1 - ((float(lineasGD[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGD = calidadGD * calidadGD
                    calidadBL = 1 - ((float(lineasBL[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadBL = calidadBL * calidadBL
                    calidadGP5 = 1 - ((float(lineasGP5[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP5 = calidadGP5 * calidadGP5
                    calidadGP15 = 1 - ((float(lineasGP15[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP15 = calidadGP15 * calidadGP15
                    calidadGP40 = 1 - ((float(lineasGP40[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP40 = calidadGP40 * calidadGP40
                    print "calidadGD = 1 - (" + str(float(lineasGD[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGD)
                    print "calidadBL = 1 - (" + str(float(lineasBL[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadBL)
                    print "calidadGP5 = 1 - (" + str(float(lineasGP5[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP5)
                    print "calidadGP15= 1 - (" + str(float(lineasGP15[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP15)
                    print "calidadGP40 = 1 - (" + str(float(lineasGP40[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP40)

                print ""
                sumatoriaGD += calidadGD
                sumatoriaBL += calidadBL
                sumatoriaGP5 += calidadGP5
                sumatoriaGP15 += calidadGP15
                sumatoriaGP40 += calidadGP40

            promedioGD = sumatoriaGD/len(lineasEX)
            promedioBL = sumatoriaBL/len(lineasEX)
            promedioGP5 = sumatoriaGP5/len(lineasEX)
            promedioGP15 = sumatoriaGP15/len(lineasEX)
            promedioGP40 = sumatoriaGP40/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGD)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBL)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP5K' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP5)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP15K' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP15)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP40K' + str(k) + 'M15COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP40)+'\n')
            s.close()


            m = int(((n * (n-1))/2)/2)

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP5', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP15', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP40', 'wb+')
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'wb+')
            f.close()


            for q in range(0,v):
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

                bashCommand = " ./algo3tp3 -EX -s -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 5 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 15 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 40 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -PS -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)


            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            f = open('../recursos/comparando/GREED', 'r')
            lineasGD = f.readlines()
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBL = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP5', 'r')
            lineasGP5 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP15', 'r')
            lineasGP15 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP40', 'r')
            lineasGP40 = f.readlines()
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'r')
            lineasPS = f.readlines()
            f.close()

            sumatoriaGD = 0
            sumatoriaBL = 0
            sumatoriaGP5 = 0
            sumatoriaGP15 = 0
            sumatoriaGP40 = 0
            for z in range(0,len(lineasEX)):
                if (float(lineasPS[z]) == float(lineasEX[z])):
                    calidadGD = 1
                    calidadBL = 1
                    calidadGP5 = 1
                    calidadGP15 = 1
                    calidadGP40 = 1
                else:
                    calidadGD = 1 - ((float(lineasGD[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGD = calidadGD * calidadGD
                    calidadBL = 1 - ((float(lineasBL[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadBL = calidadBL * calidadBL
                    calidadGP5 = 1 - ((float(lineasGP5[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP5 = calidadGP5 * calidadGP5
                    calidadGP15 = 1 - ((float(lineasGP15[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP15 = calidadGP15 * calidadGP15
                    calidadGP40 = 1 - ((float(lineasGP40[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP40 = calidadGP40 * calidadGP40
                    print "calidadGD = 1 - (" + str(float(lineasGD[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGD)
                    print "calidadBL = 1 - (" + str(float(lineasBL[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadBL)
                    print "calidadGP5 = 1 - (" + str(float(lineasGP5[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP5)
                    print "calidadGP15= 1 - (" + str(float(lineasGP15[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP15)
                    print "calidadGP40 = 1 - (" + str(float(lineasGP40[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP40)

                print ""
                sumatoriaGD += calidadGD
                sumatoriaBL += calidadBL
                sumatoriaGP5 += calidadGP5
                sumatoriaGP15 += calidadGP15
                sumatoriaGP40 += calidadGP40

            promedioGD = sumatoriaGD/len(lineasEX)
            promedioBL = sumatoriaBL/len(lineasEX)
            promedioGP5 = sumatoriaGP5/len(lineasEX)
            promedioGP15 = sumatoriaGP15/len(lineasEX)
            promedioGP40 = sumatoriaGP40/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGD)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBL)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP5K' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP5)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP15K' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP15)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP40K' + str(k) + 'M50COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP40)+'\n')
            s.close()


            m = (n * (n-1))/2

            f = open('../recursos/comparando/EXACTO', 'wb+')
            f.close()
            f = open('../recursos/comparando/GREED', 'wb+')
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP5', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP15', 'wb+')
            f.close()
            f = open('../recursos/comparando/GRASP40', 'wb+')
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'wb+')
            f.close()


            for q in range(0,v):
                nombre = 'N' + str(n) + 'K' + str(k) + 'M100COMPARACION.grafo'

                r = open(str('../recursos/comparando/' + nombre), 'wb+')

                r.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')

                for i in range(1, (n)):
                    for j in range((i+1), (n+1)):
                        w = randint(1, 999)
                        r.write(str(i) + ' ' + str(j) + ' ' + str(w) + '\n')
                r.close()
                bashCommand = " ./algo3tp3 -EX -s -p ../recursos/comparando/" + nombre + " -ph"
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GD -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 5 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 15 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -GP -m 40 -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -BL -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

                bashCommand = " ./algo3tp3 -PS -s -p ../recursos/comparando/" + nombre
                os.system(bashCommand)

            f = open('../recursos/comparando/EXACTO', 'r')
            lineasEX = f.readlines()
            f.close()
            f = open('../recursos/comparando/GREED', 'r')
            lineasGD = f.readlines()
            f.close()
            f = open('../recursos/comparando/BUSQUEDA', 'r')
            lineasBL = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP5', 'r')
            lineasGP5 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP15', 'r')
            lineasGP15 = f.readlines()
            f.close()
            f = open('../recursos/comparando/GRASP40', 'r')
            lineasGP40 = f.readlines()
            f.close()
            f = open('../recursos/comparando/PEOR_SOLUCION', 'r')
            lineasPS = f.readlines()
            f.close()


            sumatoriaGD = 0
            sumatoriaBL = 0
            sumatoriaGP5 = 0
            sumatoriaGP15 = 0
            sumatoriaGP40 = 0
            for z in range(0,len(lineasEX)):
                if (float(lineasPS[z]) == float(lineasEX[z])):
                    calidadGD = 1
                    calidadBL = 1
                    calidadGP5 = 1
                    calidadGP15 = 1
                    calidadGP40 = 1
                else:
                    calidadGD = 1 - ((float(lineasGD[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGD = calidadGD * calidadGD
                    calidadBL = 1 - ((float(lineasBL[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadBL = calidadBL * calidadBL
                    calidadGP5 = 1 - ((float(lineasGP5[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP5 = calidadGP5 * calidadGP5
                    calidadGP15 = 1 - ((float(lineasGP15[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP15 = calidadGP15 * calidadGP15
                    calidadGP40 = 1 - ((float(lineasGP40[z]) - float(lineasEX[z])) / (float(lineasPS[z]) - float(lineasEX[z])))
                    calidadGP40 = calidadGP40 * calidadGP40
                    print "calidadGD = 1 - (" + str(float(lineasGD[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGD)
                    print "calidadBL = 1 - (" + str(float(lineasBL[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadBL)
                    print "calidadGP5 = 1 - (" + str(float(lineasGP5[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP5)
                    print "calidadGP15= 1 - (" + str(float(lineasGP15[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP15)
                    print "calidadGP40 = 1 - (" + str(float(lineasGP40[z]))+"-"+str(float(lineasEX[z]))+")/("+str(float(lineasPS[z]))+"-"+str(float(lineasEX[z])) +") = "+  str(calidadGP40)

                print ""
                sumatoriaGD += calidadGD
                sumatoriaBL += calidadBL
                sumatoriaGP5 += calidadGP5
                sumatoriaGP15 += calidadGP15
                sumatoriaGP40 += calidadGP40

            promedioGD = sumatoriaGD/len(lineasEX)
            promedioBL = sumatoriaBL/len(lineasEX)
            promedioGP5 = sumatoriaGP5/len(lineasEX)
            promedioGP15 = sumatoriaGP15/len(lineasEX)
            promedioGP40 = sumatoriaGP40/len(lineasEX)

            s = open('../recursos/comparando/GREEDK' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGD)+'\n')
            s.close()
            s = open('../recursos/comparando/BUSQUEDAK' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioBL)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP5K' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP5)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP15K' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP15)+'\n')
            s.close()
            s = open('../recursos/comparando/GRASP40K' + str(k) + 'M100COMPARACION.dat', 'a+')
            s.write(str(n)+"   "+str(promedioGP40)+'\n')
            s.close()



if __name__=="__main__":main(sys.argv[1:])