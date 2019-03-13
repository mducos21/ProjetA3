#include "consigne.h"

float consigne(float csgn)
{

   if (access(".verrouConsigne", F_OK) != -1)
   {
      // Fichier existe
   }
   else
   {
      // Fichier n'existe pas
      FILE *verrou = NULL;
      verrou = fopen(".verrouConsigne", "w");
      fclose(verrou);

      FILE *fichier = NULL;
      fichier = fopen("consigne.txt", "r");

      if (fichier != NULL)
      {
         printf("coucou");
         fscanf(fichier, "%f\n", &csgn); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
         printf("%f", csgn);       // On affiche la chaîne
      }
      fclose(fichier);
      remove(".verrouConsigne");
   }
   return csgn;
}
