#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processus.h"
#include "scheduler.h"
#include "policies/fifo.c"
#include "policies/sjf.c"
#include "policies/round_robin.c"

typedef struct {
    char nom[50];
    PolitiqueOrdonnancement fonction;
} PolitiqueMenu;

int main(int argc, char* argv[]) {
    Simulation* sim;
    PolitiqueMenu menu[] = {
        {"FIFO (First In First Out)", politique_fifo},
        {"SJF (Shortest Job First)", politique_sjf},
        {"Round Robin (Quantum=2)", politique_rr},
        {"", NULL}
    };
    int choix;
    char input[10];
    int i;
    if (argc < 2) {
        printf("Usage: %s <fichier_configuration>\n", argv[0]);
        return 1;
    }

    sim = charger_processus(argv[1]);
    if (!sim) {
        printf("Erreur lors du chargement des processus\n");
        return 1;
    }
    
    printf("Fichier charge: %s\n", argv[1]);
    printf("Nombre de processus: %d\n", sim->nb_processus);
    
    printf("\n========== POLITIQUES D'ORDONNANCEMENT ==========\n");
    choix = 0;
    for (i = 0; menu[i].fonction != NULL; i++) {
        printf("%d. %s\n", i + 1, menu[i].nom);
    }
    
    printf("\nVotre choix (1-%d) [defaut=1]: ", i);
    fgets(input, sizeof(input), stdin);
    
    if (input[0] != '\n') {
        choix = atoi(input) - 1;
    }
    
    if (choix < 0 || choix >= i) {
        choix = 0; 
    }
    menu[choix].fonction(sim);
    afficher_resultats(sim);
    liberer_simulation(sim);
    
    return 0;
}
