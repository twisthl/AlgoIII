#ifndef _AUX_H
#define _AUX_H

#include <stdio.h>
#include <pthread.h>
#include <time.h>

class Reloj{
 public:
	Reloj();
	Reloj(pthread_t);

	void tick();
	void tack();
	long diferencia_tick_tack();
 private:
	clockid_t _cid;
	struct timespec _ti, _tf;
	pthread_t _thread;
};

#endif
