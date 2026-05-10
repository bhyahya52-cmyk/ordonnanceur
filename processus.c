#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processus.h"

Simulation* charger_processus(const char* fichier) {
    FILE* f;
    Simulation* sim;
    char ligne[256];
    int capacite;
    int i;
    
    f = fopen(fichier, "r");
    sim = (Simulation*)malloc(sizeof(Simulation));
    sim->processus = NULL;
    sim->nb_processus = 0;
    sim->temps_actuel = 0;
    
    capacite = 10;
    sim->processus = (Processus*)malloc(capacite * sizeof(Processus));
    
    while (fgets(ligne, sizeof(ligne), f)) {
        Processus p;
        if (sscanf(ligne, "%s %d %d %d", p.nom, &p.arrivee, &p.duree_cycle, &p.duree_io) == 4) {
            p.temps_restant = p.duree_cycle;
            p.temps_execution = 0;
            p.temps_attente = 0;
            p.debut_execution = -1;
            p.fin_execution = -1;
            p.est_termine = 0;
            
            if (sim->nb_processus >= capacite) {
                capacite *= 2;
                sim->processus = (Processus*)realloc(sim->processus, capacite * sizeof(Processus));
            }
            sim->processus[sim->nb_processus++] = p;
        }
    }
    
    fclose(f);
    return sim;
}

void liberer_simulation(Simulation* sim) {
    if (sim) {
        free(sim->processus);
        free(sim);
    }
}

void afficher_resultats(Simulation* sim) {
    int i;
    int temps_total;
    
    printf("RESULTATS DE LA SIMULATION \n\n");
    printf("%-10s %-10s %-10s %-10s %-10s\n", 
           "Processus", "Arrivee", "Duree", "Attente", "Reponse");
    printf("------------------------------------------------\n");
    
    temps_total = 0;
    for (i = 0; i < sim->nb_processus; i++) {
        Processus p = sim->processus[i];
        int temps_reponse = p.fin_execution - p.arrivee;
        temps_total += temps_reponse;
        printf("%-10s %-10d %-10d %-10d %-10d\n",
               p.nom, p.arrivee, p.duree_cycle, p.temps_attente, temps_reponse);
    }
    
    printf("\nTemps moyen de retour: %.2f\n", (float)temps_total / sim->nb_processus);
    printf("\n");
}
