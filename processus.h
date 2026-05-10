#ifndef PROCESSUS_H
#define PROCESSUS_H

typedef struct {
    char nom[50];
    int arrivee;
    int duree_cycle;
    int duree_io;
    int temps_restant;
    int temps_execution;
    int temps_attente;
    int debut_execution;
    int fin_execution;
    int est_termine;
} Processus;

typedef struct {
    Processus* processus;
    int nb_processus;
    int temps_actuel;
} Simulation;
Simulation* charger_processus(const char* fichier);
void liberer_simulation(Simulation* sim);
void afficher_resultats(Simulation* sim);

#endif
