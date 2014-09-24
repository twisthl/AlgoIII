#ifndef EJ3_H
#define EJ3_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "vector"
#include "iterator"
#include <math.h>

using namespace std;

typedef std::vector< vector<int> > MatrizAdyacencia;
typedef std::vector<Enlace> Red;

struct Enlace {
		int compu1;
		int compu2;
		int costo;
};

// class RedAnillo{

// 	private:
// 		int costoTotal;
// 		int cantEnlacesEnAnillo;
// 		int cantEnlacesFuera;
// 		std::vector<Enlace> enlacesEnAnillo;
// 		std::vector<Enlace> enlacesFuera;

// 	public:
// 		RedAnillo();
// 		~RedAnillo();

// 		/* data */
// };


#endif