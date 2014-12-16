#!/usr/bin/python
# -*- coding: utf-8 -*-

import random, math, sys
from optparse import OptionParser

#Generador de grafos al azar con distintas densidades de aristas.
def randomAlgorithm(n, d, min_weight, max_weight):	
	edgesAmount = 0
	edges_str = ""
	for i in range(0,n):
		for j in range(i+1, n):
			dice = random.random()
			if dice <= d:
				weight = random.uniform(min_weight, max_weight)
				edgesAmount = edgesAmount + 1
				edges_str += str(i+1) + " " + str(j+1) + " " + str(weight) + "\n"
		
	return edgesAmount, edges_str	
	
#Generador de grafos con formato de estrella mas ciclo. Esta familia de casos
#rompen la heuristica golosa. El peso de todas las aristas del ciclo van de [min; max]
#el peso del centro de la estrella asegura que mayor a la suma del peso de todas las aristas.
def starCicleAlgorithm(n, min_weight, max_weight):
	edgesAmount = 0
	edges_str = ""
	cicle_weight = 0.0
	center_edge = n
	for i in range(0,n):
		weight = random.uniform(min_weight, max_weight)
		cicle_weight = cicle_weight + weight
		next_edge = i+1
		edges_str += str(i+1) + " " + str(next_edge+1) + " " + str(weight) + "\n"
	
	edges_str += str(1) + " " + str(n+1) + " " + str(weight) + "\n"
		
	for i in range(0, n):
		#La arista del centro a los vertices del ciclo, siempre es mas pesada que la suma total.
		edges_str += str(i+1) + " " + str(center_edge+1) + " " + str(cicle_weight + 1.0) + "\n"
	
	return edgesAmount, edges_str

#Generador de grafos que rompe la busqueda local.
def matrixDistributionAlgorithm(n, min_weight, max_weight):
	edgesAmount = 0
	edges_str = ""
	
	for i in range(0,n):
		for j in range(0,n):
			for k in range(0, n):
				for h in range(j, n):
					row = i*n
					
					edges_str += str(1) + " " + str(n+1) + " " + str(weight) + "\n"
	
	
	


usage="Generador de inputs para < >."
parser = OptionParser(usage=usage)

parser.add_option("-n", "--size", dest="size", help="Cantidad de nodos", default=8) 
parser.add_option("-d", "--density", dest="density", help="Probabilidad de que exista una arista entre dos nodos", default=0.5)
parser.add_option("-a", "--algorithm", dest="algorithm", help="Algoritmo a utilizar: random, star+cicle", default="random")

parser.add_option("-x", "--min", dest="min_weight", help="Peso minimo", default=1.0)
parser.add_option("-y", "--max", dest="max_weight", help="Peso maximo", default=8.0)
parser.add_option("-k", "--partitions", dest="partitions", help="Cantidad de particiones del problema", default=1)
(options, args) = parser.parse_args()

size = int(options.size)
density = float(options.density)
min_weight = float(options.min_weight)
max_weight = float(options.max_weight)
partitions = int(options.partitions)
algorithm = options.algorithm

edgesAmount = 0
edges_str = ""

if options.algorithm == "random":
	edgesAmount, edges_str = randomAlgorithm(size, density, min_weight, max_weight) 
elif options.algorithm == "star+cicle":
	edgesAmount, edges_str = starCicleAlgorithm(size, min_weight, max_weight)
	size = size + 1

sys.stdout.write(str(size))
sys.stdout.write(" ")
sys.stdout.write(str(edgesAmount))
sys.stdout.write(" ")
sys.stdout.write(str(partitions))
sys.stdout.write("\n")
sys.stdout.write(edges_str)
sys.stdout.write("\n")
