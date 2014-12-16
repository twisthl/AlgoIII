#ifndef _RELOJ_H
#define _RELOJ_H

#include <time.h>
#include <list>
#include <utility>


using namespace std;

class Reloj{
 public:
	/* usaba CLOCK_PROCESS_CPUTIME_ID pero parece que anda mal*/
	Reloj(){_contando=false; _id=CLOCK_MONOTONIC;}
	Reloj(clockid_t &);
	bool operator()(int n = 0);

	typedef struct par_temporal{ 
		struct timespec principio, final;
		long lapso(){
			
			long sec_to_micro = 0;
			long nano_to_micro = 0;
			
			if ((final.tv_nsec - principio.tv_nsec) > 0) {
				nano_to_micro = (final.tv_nsec - principio.tv_nsec) / (long) 1e3 ; 
			} else {
				nano_to_micro = 0;
			}
			
			
			sec_to_micro = ( final.tv_sec - principio.tv_sec ) * (long) 1e6 ;
			cout << endl;
			cout << "Sec to micro: " << sec_to_micro << endl;
			cout << "Nano to micro: " << nano_to_micro << endl;
			cout << endl;
			//cout << "Mili: " << sec_to_milli + nano_to_milli << endl;
 			return sec_to_micro + nano_to_micro;};
	} par_temporal;

	void mostrar_tiempos();
	void promediar_tiempos();
	void mostrar_promedios();

	std::list<std::pair<int, par_temporal> >::iterator iterar_tiempos();
 	std::list<std::pair<int, par_temporal> > tiempos_lista;
	std::list<std::pair<int, long> > lapsos_promedios;

 private:

	par_temporal _en_uso;
	int _n_actual;
	clockid_t _id;
	bool _contando;

};

#endif
