#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "processus.h"
typedef void (*PolitiqueOrdonnancement)(Simulation* sim);
void politique_fifo(Simulation* sim);
void politique_sjf(Simulation* sim);
void politique_rr(Simulation* sim);
void lister_politiques();

#endif
