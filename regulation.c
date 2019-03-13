#include "regulation.h"

float regulationTest(int regul, float csgn, float *tabT, int nT)
{

	int i;
	PID_t PID;
	PID.cmd = 100.0;
	PID.erreurP = 0;
	PID.somme_erreurs = 0;
	PID.mode =1;
	for (i = 0; i < nT; i++)
	{
		PID = regulation(regul, csgn, tabT[i], i, PID);
	}

	return PID.cmd;
}

PID_t regulation(int regul, float csgn, float tabT, int i, PID_t PID)
{
	float P, I, D, erreur, Kp, Ki, Kd;
	switch (PID.mode)
	{
	case 1:
		Kp = 1 ;
		Ki = 0.1 ;
		Kd = 0.1 ;
		break;
	case 2:
		Kp = 1 ;
		Ki = 0.1 ;
		Kd = 0.1 ;
		break;
	case 3:
		Kp = 1 ;
		Ki = 1 ;
		Kd = 1 ;
		break;
	default:
		break;
	}

	switch (regul)
	{
	case 1:
		if (csgn < tabT)
		{
			PID.cmd = 0;
		}
		if (csgn > tabT)
		{
			PID.cmd = 40.0;
		}

		break;
	case 2:
		erreur = csgn - tabT;

		PID.somme_erreurs += (((erreur + PID.erreurP) * 10) / 2);
		P = Kp * erreur;
		I = Ki * PID.somme_erreurs;
		D = Kd * (erreur - PID.erreurP) / 10;
		printf("P:%.2f\n", P);
		if (i == 0)
		{
			D = 0;
			I = 0;
			PID.somme_erreurs = 0;
		}
		printf("I:%.2f\n", I);
		printf("D:%.2f\n\n", D);
		PID.cmd = P + I + D;

		PID.erreurP = erreur;
		printf("cmd:%.2f\n\n", PID.cmd);

		if (PID.cmd > 100)
		{
			PID.cmd = 100;
		}
		if (PID.cmd <0) {
			PID.cmd =0;
		}
		

		break;

	default:
		PID.cmd = 0;
		break;
	}
	return PID;
}
