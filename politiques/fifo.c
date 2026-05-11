#include "../processus.h"
#include <stdio.h>
#include <stdlib.h>

void politique_fifo(Simulation* sim) {
    int temps = 0;
    int processus_termines = 0;
    int* termine;
    int i;
    int idx;
    int arrivee_min;
    
    printf("\n--- Execution avec politique FIFO ---\n");
    
    termine = (int*)calloc(sim->nb_processus, sizeof(int));
    
    while (processus_termines < sim->nb_processus) {
        idx = -1;
        arrivee_min = 999999;
        
        for (i = 0; i < sim->nb_processus; i++) {
            if (!termine[i] && sim->processus[i].arrivee <= temps) {
                if (sim->processus[i].arrivee < arrivee_min) {
                    arrivee_min = sim->processus[i].arrivee;
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            temps++;
            continue;
        }
        
        if (sim->processus[idx].debut_execution == -1)
            sim->processus[idx].debut_execution = temps;
        
        printf("T=%d: Execution de %s\n", temps, sim->processus[idx].nom);
        
        temps += sim->processus[idx].duree_cycle;
        sim->processus[idx].fin_execution = temps;
        termine[idx] = 1;
        processus_termines++;
        sim->processus[idx].temps_attente = sim->processus[idx].debut_execution - sim->processus[idx].arrivee;
    }
    
    free(termine);
}
