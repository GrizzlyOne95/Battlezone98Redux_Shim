/*
 * Entry: 0050f109
 * Name: add_or_subtract
 * Namespace: Global
 * Signature: double add_or_subtract(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
add_or_subtract(_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,
               char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  char (*pacVar4) [80];
  int extraout_EAX;
  double dVar5;
  double local_18;
  int local_10;
  int local_c;
  int local_8;
  
  pacVar4 = param_6;
  iVar3 = param_3;
  piVar2 = param_2;
  local_18 = multiply_or_divide(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_8,
                                (int *)&param_2,param_10);
  if (*piVar2 <= iVar3) {
    while( true ) {
      cVar1 = pacVar4[*piVar2][0];
      param_3 = CONCAT13(cVar1,(undefined3)param_3);
      if ((cVar1 != '+') && (cVar1 != '-')) break;
      *piVar2 = *piVar2 + 1;
      dVar5 = multiply_or_divide(param_1,piVar2,iVar3,param_4,param_5,pacVar4,param_7,&local_10,
                                 &local_c,param_10);
      if ((local_8 == 0) || (local_10 == 0)) {
        local_8 = 0;
        if (param_3._3_1_ == '+') {
          local_18 = dVar5 + local_18;
        }
        else {
          local_18 = local_18 - dVar5;
        }
      }
      else {
        local_8 = 1;
        if (param_3._3_1_ == '+') {
          param_2 = (int *)((int)param_2 + local_c);
        }
        else {
          param_2 = (int *)((int)param_2 - local_c);
        }
      }
    }
  }
  *param_8 = local_8;
  if (local_8 == 0) {
    _ftol2_sse();
    *param_9 = extraout_EAX;
    return local_18;
  }
  *param_9 = (int)param_2;
  return (double)(int)param_2;
}
