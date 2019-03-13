#include "visualisationC.h"


void visualisationC(float puissance_f)
{
   
   float tint, text;

   if( access( ".verrouData", F_OK ) != -1 )
   {
      // File unvailable
   }else{
      // Creating the lock file to prevent a change of values at the same time
      FILE *verrou = NULL;
      verrou = fopen(".verrouData", "w");
      fclose(verrou);

      // Opening the data.txt file in read mode
      FILE *data = NULL;
      data = fopen("data.txt", "r");

      // The indoor and outdoor temperature values are retrieved
      if (data != NULL)
      {
            fscanf(data, "%f\n%f\n", &text, &tint);
      }
      fclose(data);

      // Opening the data.txt file in w+ mode
      FILE *data2 = NULL;
      data2 = fopen("data.txt", "w+");

      // Writing data.txt in function of puissance_f
      // If puissance_f = 0 then we write the same values of temperature than before and we write false at the last line
      // Else we write true at the last line
      if (puissance_f == 0) {
         fprintf(data2, "%.2f\n%.2f\nfalse", text, tint);
      }
      else {
         fprintf(data2, "%.2f\n%.2f\ntrue", text, tint);
      }
      fclose(data2);

      // Removing .verrouData
      remove(".verrouData");
      
   }
}
