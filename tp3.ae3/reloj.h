#ifndef _RELOJ_H
#define _RELOJ_H

#include <time.h>
#include <list>
#include <vector>
#include <utility>

typedef enum { MILLI_SEC = 0, MICRO_SEC = 1, NANO_SEC = 2} ConvertionEnum;

using namespace std;

class Reloj{
 public:
	/* usaba CLOCK_PROCESS_CPUTIME_ID pero parece que anda mal*/
	Reloj(){_convertion = MICRO_SEC; _contando=false; _id=CLOCK_MONOTONIC_RAW;}
	Reloj(ConvertionEnum convertion){_convertion = convertion; _contando=false; _id=CLOCK_MONOTONIC_RAW;}
	Reloj(clockid_t id){_convertion = MICRO_SEC; _contando=false; _id=id;};
	Reloj(clockid_t id, ConvertionEnum convertion){_convertion = convertion; _contando=false; _id=CLOCK_MONOTONIC_RAW;};

	bool operator()(int n = 0);

	typedef struct par_temporal{ 
		struct timespec principio, final;
		long lapso(ConvertionEnum convertion){
			
			long sec_conv_factor;
			long nano_conv_factor;
			if (convertion == MILLI_SEC) {
				sec_conv_factor = 1e3;
				nano_conv_factor = 1e6;
			} else if (convertion == MICRO_SEC) {
				sec_conv_factor = 1e6;
				nano_conv_factor = 1e3;
			} else if (convertion == NANO_SEC) {
				sec_conv_factor = 1e9;
				nano_conv_factor = 1;
			}

			long converted_sec = 0;
			long converted_nano = 0;
			
			if ( ( final.tv_nsec - principio.tv_nsec ) > 0 )
				converted_nano = ( final.tv_nsec - principio.tv_nsec ) / nano_conv_factor;
			else
				converted_nano = 0;
						
			converted_sec = ( final.tv_sec - principio.tv_sec ) * sec_conv_factor ;
			
 			return converted_sec + converted_nano;};
	} par_temporal;

	void mostrar_tiempos();
	void promediar_tiempos();
	void mostrar_promedios();

	std::list<std::pair<int, par_temporal> >::iterator iterar_tiempos();
 	std::list<std::pair<int, par_temporal> > tiempos_lista;
	std::list<std::pair<int, long> > lapsos_promedios;

 private:
	ConvertionEnum _convertion;
	vector<par_temporal> _pares_temporales;
	//par_temporal _en_uso;
	int _n_actual;
	clockid_t _id;
	bool _contando;

};

#endif
