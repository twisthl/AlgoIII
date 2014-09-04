#include "aux.h"

using namespace std;

Reloj::Reloj()
{
	_cid = CLOCK_THREAD_CPUTIME_ID;
	Reloj(pthread_self());
};

Reloj::Reloj(pthread_t p)
{
	_cid = CLOCK_THREAD_CPUTIME_ID;
	if ( pthread_getcpuclockid(_thread, &_cid) ) 
		perror("Generando Clock"); 
};

void Reloj::tick()
{ 
	if ( clock_gettime(_cid, &_ti) ) 
		perror("Obteniendo tiempo"); 
};

void Reloj::tack()
{ 
	if ( clock_gettime(_cid, &_tf) ) 
		perror("Obteniendo tiempo"); 
};

long Reloj::diferencia_tick_tack()
{ 
	return ( _tf.tv_nsec - _ti.tv_nsec ) % (long) 1e9 + ( _tf.tv_sec - _ti.tv_sec ) * (long) 1e9;
};


