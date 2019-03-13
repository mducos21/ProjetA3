#include "define.h"
#include "releve.h"
#include "commande.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h" 



int main(){

    int i = 0;
    int mode;
    float csgn;
    
    // Creation des structures
    temp_t Temperature_Recue;
    Temperature_Recue.interieure = 0;
    Temperature_Recue.exterieure = 0;

    PID_t PID;
    PID.cmd = 100;
    PID.erreurP = 0;
    PID.somme_erreurs = 0;
    PID.mode = 3;

    // Definition des variables pour la liaison USB
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    /* Choix du mode :
     * 1 = ToR
     * 2 = PID
     */
    mode = 1;

    // Initialisation USB
    ftStatus = FT_Open(0,&ftHandle);
    if (ftStatus != FT_OK) {
         // la connexion a la carte ne fonctionne pas, on quitte le programme
        return EXIT_FAILURE;
    }
    
    // On fait une boucle dans les élèments en fonction de csgn

    do{
        Temperature_Recue = releve(ftHandle, ftStatus);
        visualisationT(Temperature_Recue);
        csgn = consigne(csgn);
        PID = regulation(mode, csgn, Temperature_Recue.interieure, i, PID);
        visualisationC(PID.cmd);
        commande(PID.cmd, ftHandle, ftStatus);
        i++;
    }while(csgn > 5);
    
    // Fermeture de la connexion a la carte
    FT_Close(ftHandle);
    return 0;
}
