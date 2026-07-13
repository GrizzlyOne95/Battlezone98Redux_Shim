/*
 * Entry: 00511f64
 * Name: IParse_Parse_New_Command
 * Namespace: Global
 * Signature: void IParse_Parse_New_Command(char * param_1, int * param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
IParse_Parse_New_Command
          (char *param_1,int *param_2,int *param_3,double *param_4,char (*param_5) [80],int *param_6
          )

{
  char cVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  int local_8;
  
  local_8 = 0;
  *param_2 = 0;
  cVar1 = *param_1;
  do {
    if (cVar1 == '\0') {
      return;
    }
    iVar2 = IParse_Next_Symbol(param_1,&local_8,param_5[*param_2]);
    if (iVar2 == 1) {
      iVar3 = atoi(param_5[*param_2]);
      param_3[*param_2] = iVar3;
      param_4[*param_2] = (double)param_3[*param_2];
LAB_00511fc0:
      dVar4 = -1.0;
    }
    else {
      param_3[*param_2] = -1;
      if (iVar2 != 3) goto LAB_00511fc0;
      dVar4 = atof(param_5[*param_2]);
    }
    param_4[*param_2] = dVar4;
    param_6[*param_2] = iVar2;
    *param_2 = *param_2 + 1;
    cVar1 = param_1[local_8];
  } while( true );
}
