#include "releve.h"


temp_t releve( FT_HANDLE ftHandle, FT_STATUS ftStatus){
    
    // Definition des variables pour la fonction
    unsigned int SOTint, SOText;

    // Variable pour la liaison USB
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[256];

    
    // Création d'une Structure temp_t avec des valeurs de bases

    temp_t Temp;
    Temp.interieure = 0;
    Temp.exterieure = 0;

    
    // Reception des données envoyées par la carte
    FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (RxBytes > 0) {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived);
        if (ftStatus != FT_OK) {
            // La reception a echouee, on renvoie la structure de base
            return Temp;
        }
    }

    /*
     * On cherche à savoir quel octet à été envoyé en premier
     *      premier, second ou troisième de Tint
     *      premier, second ou troisième de Text
     *      7 possibilitées au total : 0x00, 0x10, 0x20, 0x80, 0x90, 0xA0 et Default (renvoie les temperatures de base)
     */
    switch (RxBuffer[0] & 0xF0){
        case 0x00:
            SOText = ((RxBuffer[0]&0x0F)<<8) + ((RxBuffer[1]&0x0F)<<4) + (RxBuffer[2]&0x0F);
            SOTint = ((RxBuffer[3]&0x0F)<<8) + ((RxBuffer[4]&0x0F)<<4) + (RxBuffer[5]&0x0F);
            break;

        case 0x10:
            SOText = ((RxBuffer[5]&0x0F)<<8) + ((RxBuffer[0]&0x0F)<<4) + (RxBuffer[1]&0x0F);
            SOTint = ((RxBuffer[2]&0x0F)<<8) + ((RxBuffer[3]&0x0F)<<4) + (RxBuffer[4]&0x0F);
            break;
        
        case 0x20:
            SOText = ((RxBuffer[4]&0x0F)<<8) + ((RxBuffer[5]&0x0F)<<4) + (RxBuffer[0]&0x0F);
            SOTint = ((RxBuffer[1]&0x0F)<<8) + ((RxBuffer[2]&0x0F)<<4) + (RxBuffer[3]&0x0F);
            break;

        case 0x80:
            SOText = ((RxBuffer[3]&0x0F)<<8) + ((RxBuffer[4]&0x0F)<<4) + (RxBuffer[5]&0x0F);
            SOTint = ((RxBuffer[0]&0x0F)<<8) + ((RxBuffer[1]&0x0F)<<4) + (RxBuffer[2]&0x0F);
            break;

        case 0x90:
            SOText = ((RxBuffer[2]&0x0F)<<8) + ((RxBuffer[3]&0x0F)<<4) + (RxBuffer[4]&0x0F);
            SOTint = ((RxBuffer[5]&0x0F)<<8) + ((RxBuffer[0]&0x0F)<<4) + (RxBuffer[1]&0x0F);
            break;

        case 0xA0:
            SOText = ((RxBuffer[1]&0x0F)<<8) + ((RxBuffer[2]&0x0F)<<4) + (RxBuffer[3]&0x0F);
            SOTint = ((RxBuffer[4]&0x0F)<<8) + ((RxBuffer[5]&0x0F)<<4) + (RxBuffer[0]&0x0F);
            break;

        default:
            printf("Un problème à été détecté lors de la reception des données, veuillez réessayer !");
            return Temp;
    }

    /*
     * Calcul de la temperature interieure et exterieure
     *      temperature = -39.64 + 0.04 * SOT;
     */
    Temp.interieure = -39.64 + 0.04 * SOTint;
    Temp.exterieure = -39.64 + 0.04 * SOText;

    // Modification de la temperature intérieure si celle ci est supérieure à 40.90°C 
    if (Temp.interieure > 40.96){
        Temp.interieure = 40.96;
    }

    return Temp;
}
