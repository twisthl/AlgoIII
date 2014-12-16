#include <time.h>
#include <math.h>
#include <utility>
#include <iostream>
#include "reloj.h"

std::list<std::pair<int, Reloj::par_temporal> >::iterator
iterar_tiempos(){
	std::list<std::pair<int, Reloj::par_temporal> >::iterator it;
	return it;
}

/* Ver man clock_gettime para los distintos tipos posibles de ID
Ojo si se usa CLOCK_PROCESS_CPUTIME_ID :

Note for SMP systems
The CLOCK_PROCESS_CPUTIME_ID and CLOCK_THREAD_CPUTIME_ID clocks are realized on many platforms using timers from  the  CPUs  (TSC  on  i386, AR.ITC  on  Itanium).   These  registers  may differ between CPUs and as a consequence these clocks may return bogus results if a process is
       migrated to another CPU.
*/

bool Reloj::operator()(int n){
		if (!_contando && n != 0) {
			par_temporal medicion;
			clock_gettime(_id, &medicion.principio);
			_pares_temporales.push_back(medicion);
			_n_actual = n;
		} else if(_contando) {
			par_temporal& medicion = _pares_temporales.back();
			clock_gettime(_id, &medicion.final);
			//cout << "principio: " << _en_uso.principio.tv_nsec << endl;
			//cout << "final - principio: " << medicion.final.tv_nsec - medicion.principio.tv_nsec << endl;
			tiempos_lista.push_back(std::make_pair(_n_actual, medicion));
		}
		else std::cerr << "Reloj error: se debe inicializar con un n" << std::endl;
		_contando =! _contando;
		return _contando;
}

void Reloj::mostrar_tiempos(){
	
	std::list<std::pair<int, Reloj::par_temporal> >::iterator it;
	it = tiempos_lista.begin();
	
	std::cerr << "tamaño\ttiempo" << std::endl;
	for(; it != tiempos_lista.end(); ++it){
		std::cout << it->first << "\t" << it->second.lapso(_convertion) << std::endl;
	}
	
}

void Reloj::mostrar_promedios(){
	std::list<std::pair<int, long> >::iterator it = lapsos_promedios.begin();
	for(; it != lapsos_promedios.end(); ++it){
		std::cout << it->first << "\t" << it->second << std::endl;
	}
}

void Reloj::promediar_tiempos(){
	std::list<std::pair<int, par_temporal> > aux;
	
	int muestra_size = tiempos_lista.size();
	
	while( tiempos_lista.size() > 0){
		std::pair<int, par_temporal> e = tiempos_lista.front();
		std::list<std::pair<int, par_temporal> >::iterator it = tiempos_lista.begin();
		long lapso = 0;
		long muestra_size = tiempos_lista.size();
		for(; it != tiempos_lista.end(); ++it){
			if( it->first == e.first ){
				//cout << "lapso: " << it->second.lapso(_convertion) << endl;
				if (_convertion == MICRO_SEC || _convertion == NANO_SEC) {
					lapso = lapso + ( it->second.lapso(_convertion) / muestra_size);
				} else {
					lapso = lapso + it->second.lapso(_convertion);
				}
				aux.push_back(*it);
				it = tiempos_lista.erase(it);
				it--;				
			}
		}
		if (_convertion == MILLI_SEC) {
			lapso = lapso / muestra_size;
		}
		//cout << "debug: " << lapso << endl;
		lapsos_promedios.push_back(std::make_pair(e.first, lapso ) );
	}
	tiempos_lista = aux;
}
