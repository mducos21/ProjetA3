#include "define.h"

typedef struct
{
	float cmd;
	float erreurP;
	float somme_erreurs;
	int mode;
} PID_t;

float regulationTest(int regul, float csgn, float *tabT, int nT);
PID_t regulation(int regul, float csgn, float tabT, int i, PID_t PID);

