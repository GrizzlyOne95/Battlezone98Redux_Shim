/*
 * Entry: 0050ef29
 * Name: exponent
 * Namespace: Global
 * Signature: double exponent(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
exponent(_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,char (*param_6) [80]
        ,int *param_7,int *param_8,int *param_9,int *param_10)

{
  int *piVar1;
  char (*pacVar2) [80];
  int extraout_EAX;
  int extraout_EAX_00;
  char (*pacVar3) [80];
  char (*pacVar4) [80];
  float10 extraout_ST0;
  float10 fVar5;
  double dVar6;
  double local_14;
  int local_c;
  int local_8;
  
  pacVar2 = param_6;
  piVar1 = param_2;
  local_14 = negation(param_1,param_2,param_3,param_4,param_5,param_6,param_7,(int *)&param_2,
                      (int *)&param_6,param_10);
  pacVar3 = (char (*) [80])param_2;
  pacVar4 = param_6;
  if (pacVar2[*piVar1][0] == '^') {
    *piVar1 = *piVar1 + 1;
    dVar6 = exponent(param_1,piVar1,param_3,param_4,param_5,pacVar2,param_7,&local_8,&local_c,
                     param_10);
    if ((param_2 == (int *)0x0) || (local_8 == 0)) {
      fVar5 = (float10)__CIpow();
      local_14 = (double)fVar5;
      pacVar3 = (char (*) [80])0x0;
      pacVar4 = param_6;
    }
    else {
      param_6 = (char (*) [80])0x0;
      pacVar3 = (char (*) [80])0x1;
      pacVar4 = pacVar3;
      if (0.0 < dVar6) {
        _ftol2_sse();
        do {
          pacVar4 = (char (*) [80])((int)pacVar4 * extraout_EAX);
          param_6 = (char (*) [80])(*param_6 + 1);
        } while ((float10)(int)param_6 < extraout_ST0);
      }
    }
  }
  param_6 = pacVar4;
  *param_8 = (int)pacVar3;
  if (pacVar3 == (char (*) [80])0x0) {
    _ftol2_sse();
    *param_9 = extraout_EAX_00;
    return local_14;
  }
  *param_9 = (int)param_6;
  return (double)(int)param_6;
}
