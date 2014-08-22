#ifndef EJ1_H
#define EJ1_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "vector"
#include "iterator"


using namespace std;

typedef std::vector<int> LTablonesEstado;
typedef std::vector<int> LSaltos;


LSaltos resolver(int cantTablones, int saltoMaximo, LTablonesEstado& tablones);

void imprimirResultado(LSaltos);

#endif