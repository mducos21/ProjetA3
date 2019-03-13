#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    char tint[TAILLE_MAX];
    char text[TAILLE_MAX];
    char chauffage[TAILLE_MAX];
    

    if( access( ".verrouData", F_OK ) != -1 ){
        // File unvailable
    }else{
        // Creating the lock file to prevent a change of values at the same time
        FILE *verrou = NULL;
        verrou = fopen(".verrouData", "w");
        fclose(verrou);

        // Opening the data.txt file in read mode
        FILE *data = NULL;
        data = fopen("data.txt", "r");

        // The indoor and outdoor temperature values are retrieved like heating value
        if (data != NULL)
        {
            fgets(text, TAILLE_MAX, data);
            fgets(tint, TAILLE_MAX, data);
            fgets(chauffage, TAILLE_MAX, data);
        }
        fclose(data);

        // Opening the data.txt file in w+ mode
        FILE *data2 = NULL;
        data2 = fopen("data.txt", "w+");
        
        // Writing indoor and outdoor temperature value and Rewriting heating value
        fprintf(data2, "%.2f\n%.2f\n%s", myTemp.exterieure, myTemp.interieure, chauffage);
        fclose(data2); 

        remove(".verrouData"); 
    }
    
}
