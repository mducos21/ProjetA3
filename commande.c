#include "commande.h"


int commande(int puissance, FT_HANDLE ftHandle, FT_STATUS ftStatus){

    // Definition des variables
    DWORD BytesWritten;
    unsigned char TxBuffer[1];
    int PUIS;

    // On converti la puissance (en %) en valeur comprise entre 0 et 127
    PUIS = puissance * 127 / 100;
    PUIS &=~ (1<<7);

    // Ecriture de la valeur de la puissance dans le buffer
    TxBuffer[0] = PUIS;

    /*
    * On envoie la valeur du buffer a la carte en liaison USB
    * on verifie que l'ecriture de la valeur s'est bien faite sinon on quitte la fonction
    */
    ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
    if (ftStatus != FT_OK) {
        // L'écriture à ratée, on quitte la fonction
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}