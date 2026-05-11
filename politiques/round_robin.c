#include "../processus.h"
#include <stdio.h>
#include <stdlib.h>

#define QUANTUM 2

void politique_rr(Simulation* sim) {
    int temps = 0;
    int processus_termines = 0;
    int* temps_restant;
    int* termine;
    int queue[100];
    int debut = 0, fin = 0;
    int dans_queue[100];
    int i;
    int idx;
    int temps_quantum;
    
    printf("\n--- Execution avec politique Round Robin (Quantum=%d) ---\n", QUANTUM);
    
    temps_restant = (int*)malloc(sim->nb_processus * sizeof(int));
    termine = (int*)calloc(sim->nb_processus, sizeof(int));
    
    for (i = 0; i < 100; i++) {
        dans_queue[i] = 0;
    }
    
    for (i = 0; i < sim->nb_processus; i++) {
        temps_restant[i] = sim->processus[i].duree_cycle;
    }
    
    while (processus_termines < sim->nb_processus) {
        for (i = 0; i < sim->nb_processus; i++) {
            if (!termine[i] && !dans_queue[i] && sim->processus[i].arrivee <= temps && temps_restant[i] > 0) {
                queue[fin++] = i;
                dans_queue[i] = 1;
            }
        }
        
        if (debut == fin) {
            temps++;
            continue;
        }
        
        idx = queue[debut++];
        dans_queue[idx] = 0;
        
        if (sim->processus[idx].debut_execution == -1)
            sim->processus[idx].debut_execution = temps;
        
        printf("T=%d: Execution de %s\n", temps, sim->processus[idx].nom);
        
        temps_quantum = (temps_restant[idx] < QUANTUM) ? temps_restant[idx] : QUANTUM;
        temps += temps_quantum;
        temps_restant[idx] -= temps_quantum;
        
        if (temps_restant[idx] == 0) {
            sim->processus[idx].fin_execution = temps;
            termine[idx] = 1;
            processus_termines++;
            sim->processus[idx].temps_attente = sim->processus[idx].debut_execution - sim->processus[idx].arrivee;
        } else {
            queue[fin++] = idx;
            dans_queue[idx] = 1;
        }
    }
    
    free(temps_restant);
    free(termine);
}
