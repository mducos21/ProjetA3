#include "integration.h"
#include "regulation.h"
#include "visualisationT.h"
#include "visualisationC.h"

void integrationTest(int regul,temp_t tInit,int nIterations){

    // Réalisation de deux blocs pour les deux intégrations différentes (Tout ou Rien / PID)
    switch (regul)
    {
        int i;
        case 1: // Tout ou rien
            /* code */
            for( i = 0; i <= nIterations; i++){
               
            }
            break;

        case 2: // PID
            /* code */
            break;
        
        default:
            break;
    }
}
