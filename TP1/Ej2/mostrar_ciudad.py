#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt

def plot_edificio(izq,alt,der):
    plt.plot([float(izq), float(izq), float(der), float(der)], [0, float(alt), float(alt), 0], "k-", linewidth=2)
    
if __name__ == "__main__":

    fedificios = open( sys.argv[1], 'r')

    minimo = 1000000.0
    maximo = 0.0
    altura = 0.0
    ins = 0

    for linea in fedificios:

        linea = linea.split()

        if len(linea) == 1:
            ins+=1
            if ins > 1:
                break
        else:

            linea_f = map(float, linea)

            print linea_f

            if linea_f[0] < minimo:
                minimo = linea_f[0]

            if altura < linea_f[1]:
                altura = linea_f[1]

            if maximo < linea_f[2]:
                maximo = linea_f[2]

            plot_edificio(linea[0], linea[1], linea[2])

    # ahora la solución, como puntos encimados

    if len(sys.argv) > 2:

        fsolucion = open( sys.argv[2], 'r')
        for linea in fsolucion:
            linea = linea.split()
            map(float, linea)

            for i in range(0, len(linea)-1, 2):
                print linea[i], linea[i+1]
                plt.plot(linea[i], linea[i+1], 'ro')
            #por ahora solo la 1er solucion

            break 

    print minimo, maximo
    minimo -= 0.1*(maximo-minimo)
    maximo += 0.1*(maximo-minimo)
    altura *= 1.2

    plt.axis([minimo, maximo, 0, altura])
    plt.show()

    # solo la silueta

    if len(sys.argv) > 2:

        fsolucion = open( sys.argv[2], 'r')

        for linea in fsolucion:
            linea = linea.split()
            map(float, linea)

            a = 0.0
            aux = [0.0, 0.0]
            for i in range(0, len(linea)-1, 2):
                aux.append(linea[i])
                aux.append(a)
                aux.append(linea[i])
                aux.append(linea[i+1])
                a = linea[i+1]
                

            print aux

            plt.plot(aux[0::2], aux[1::2], 'k-', linewidth=2)
            #por ahora solo la 1er solucion

            break 
    
        plt.axis([minimo, maximo, 0, altura])
        plt.show()
