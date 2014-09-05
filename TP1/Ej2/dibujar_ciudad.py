#!/usr/bin/python 
#_*_ coding: utf-8 _*_

# este código no sigue mucho las buenas prácticas ... usa demasiadas variables globales, que podrían ser parámetros de funcion, pero bueno
# transparencia referencial chupame las bolas - si igual hay input de usuario así que...

import sys
import pygame

pygame.init()



(ancho, alto) = (800, 600)

pantalla = pygame.display.set_mode((ancho, alto))

blanco = [255,255,255]
negro = [0, 0, 0]
rojo = [255, 0, 0]
verde = [0, 255, 0]
azul = [0, 0, 255]

Ctrl_Code = 64

verbose = True
dibujando_edificio = False
grilla_activada = False
grilla = []
grilla_params = (40, 40)
anclaje_x = 0

edificios = []

def ubicar(a, lst, es_y = False):
    for i in range(0, len(lst)):
        if a < lst[i]:
            break

    if not es_y:
        if (lst[i] - a) < (a - lst[i-1]):
            a = lst[i]
        else:
            a = lst[i-1]
    else:
        if (lst[i-1] - a) < ( a - lst[i]):
            a = lst[i]
        else:
            a = lst[i-1]
    return a


def mostrar_ayuda():
    print "comandos de teclado: "
    print "\ts:        guardar dibujo en archivo"
    print "\tg:        activar / desactivar grilla"
    print "\t+:        en modo grilla, aumenta las divisiones verticales"
    print "\t-:        en modo grilla, disminuye las divisiones verticales"
    print "\tCtrl t+:  en modo grilla, aumenta las divisiones horizontales"
    print "\tCtrl t-:  en modo grilla, disminuye las divisiones horizontales"
    print "\tv:        modo parlanchin"
    print "\ta: ayuda"
    print "\tEsc: salir"

def alejar_grilla(i):
    global grilla_params
    a, b = grilla_params
    if pygame.key.get_mods() == Ctrl_Code:
        grilla_params = (a, b + i)
    else:
        grilla_params = (a + i, b)
    recalcular_grilla()

def acercar_grilla(i):
    global grilla_params
    a, b = grilla_params
    if pygame.key.get_mods() == Ctrl_Code:
        if ( b - i ) > 1:
            grilla_params = (a, b - i)
        else:
            grilla_params = (a, 2)
    else:
        if ( a - i ) > 1:
            grilla_params = (a - i, b)
        else:
            grilla_params = ( 2 , b)
    recalcular_grilla()


def recalcular_grilla():
    global alto, ancho, grilla_params, grilla
    x_div, y_div = grilla_params
    grilla = []
    aux = []

    for i in range(0, ancho, x_div):
        aux.append(i)
    grilla.append(aux)

    aux = []
    for i in range(0, alto, y_div):
        aux.append(i)

    grilla.append(aux)


def switch_grid():
    global grilla, grilla_activada
    if grilla_activada:
        grilla_activada = False
    else:
        recalcular_grilla()
        grilla_activada = True

def dibujar_grilla():
    global grilla, grilla_activada
    if grilla_activada:
        for i in grilla[0]:
            pygame.draw.line(pantalla, verde, (i, 0), (i, alto), 1)
        for j in grilla[1]:
            pygame.draw.line(pantalla, verde, (0, j), (ancho, j), 1)
        

def guardar_ciudad():
    global edificios
    archivo = raw_input("escriba el nombre de archivo: ")
    
    print "guardando..."

    farch = open("./res.d/"+archivo, 'w')

    formato = str(len(edificios)) + "\n"
    for e in edificios:
        formato += str(e[0]) + " " + str(alto-e[1]) + " " + str(e[2])
        formato += "\n"
    formato += "0\n"

    farch.write(formato)
    farch.close()

    print "archivo, " + archivo + " guardado."

def dibujar_anteriores():
    global edificios, alto
    
    for e in edificios:
        x, y, z = e[0], e[1], e[2]
        pygame.draw.line(pantalla, negro, (x, alto), (x, y), 2)
        pygame.draw.line(pantalla, negro, (x, y), (z, y), 2)
        pygame.draw.line(pantalla, negro, (z, alto), (z, y), 2)


def agregar_edificio((x, y)):
    global dibujando_edificio, edificios, anclaje_x, verbose
    if dibujando_edificio:
        dibujando_edificio = False
        if grilla_activada:
            x = ubicar(x, grilla[0])
            y = ubicar(y, grilla[1], True)

        if x < anclaje_x:
            tmp = anclaje_x
            anclaje_x = x
            x = tmp
        
        if not edificios.count([anclaje_x, y, x]):
            if verbose:
                print "edificio agregado ..."
            edificios.append([anclaje_x, y, x])
        else:
            if verbose:
                print "ya agregaste ese edificio ..."

    else:
        if verbose:
            print "haga click en otra esquina para crear el edificio"
        dibujando_edificio = True
        esquina = (x, y)

def undo():
    global dibujando_edificio, anclaje_x
    if dibujando_edificio:
        dibujando_edificio = False
    else:
        if len(edificios):
            anclaje_x = edificios.pop()[0]
            dibujando_edificio = True
        else:
            if verbose: 
                print "nada que deshacer!"
    

def dibujar_edificio((x, y)):

    global dibujando_edificio, alto, anclaje_x, grilla

    if grilla_activada:
        x = ubicar(x, grilla[0])
        y = ubicar(y, grilla[1], True)

    if dibujando_edificio:
        u = anclaje_x
        pygame.draw.line(pantalla, rojo, (u, alto), (u, y), 2)
        pygame.draw.line(pantalla, rojo, (u, y), (x, y), 2)
    else:
        anclaje_x = x
    pygame.draw.line(pantalla, rojo, (x, alto), (x, y), 2)

def actualizar_buffer_pantalla():
    pantalla.fill(blanco)
    dibujar_anteriores()
    dibujar_grilla()
    dibujar_edificio(pygame.mouse.get_pos())



pantalla.fill(blanco)
pygame.display.flip()
pygame.key.set_repeat(300,15)

while 1: 

    for evento in pygame.event.get():

        if evento.type == pygame.QUIT: 
            print "saliendo..."
            sys.exit()

        elif evento.type == pygame.KEYDOWN:

            if pygame.key.get_pressed()[pygame.K_s]:
                guardar_ciudad()
                if verbose:
                    print "guardando ..."

            elif pygame.key.get_pressed()[pygame.K_u]:
                undo()

            elif pygame.key.get_pressed()[pygame.K_g]:
                switch_grid()

            elif pygame.key.get_pressed()[pygame.K_a]:
                mostrar_ayuda()

            elif pygame.key.get_pressed()[pygame.K_v]:
                verbose != verbose
                print "modo parlanchin: " + str(verbose)

            elif pygame.key.get_pressed()[pygame.K_ESCAPE]:
                evento_salida = pygame.event.Event(pygame.QUIT, {})
                pygame.event.post(evento_salida)

            elif pygame.key.get_pressed()[pygame.K_PLUS]:
                if grilla_activada:
                    alejar_grilla(1)

            elif pygame.key.get_pressed()[pygame.K_MINUS]:
                if grilla_activada:
                    acercar_grilla(1)

            actualizar_buffer_pantalla()


        elif evento.type == pygame.MOUSEBUTTONDOWN:
            agregar_edificio(pygame.mouse.get_pos())

        elif evento.type == pygame.MOUSEMOTION:
            actualizar_buffer_pantalla()

    pygame.display.flip()



