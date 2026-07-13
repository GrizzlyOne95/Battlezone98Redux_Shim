/*
 * Entry: 0050ee1f
 * Name: constant_or_variable
 * Namespace: Global
 * Signature: double constant_or_variable(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
constant_or_variable
          (_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  int iVar1;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar2;
  float10 fVar3;
  float10 extraout_ST0;
  int local_8;
  
  fVar3 = (float10)0;
  iVar2 = *param_2;
  local_8 = -1;
  iVar1 = param_7[iVar2];
  if (iVar1 == 3) {
    _ftol2_sse();
    *param_9 = extraout_EAX;
    fVar3 = (float10)param_5[*param_2];
    *param_8 = 0;
  }
  else if (iVar1 == 1) {
    *param_9 = param_4[iVar2];
    fVar3 = (float10)param_4[*param_2];
    *param_8 = 1;
  }
  else if (iVar1 == 4) {
    IParse_Get_Runtime_Double(param_1,param_6[iVar2],&local_8);
    if (local_8 == -1) {
      IParse_Get_Runtime_Float(param_1,param_6[*param_2],&local_8);
      if (local_8 == -1) {
        iVar2 = IParse_Get_Runtime_Int(param_1,param_6[*param_2],&local_8);
        *param_9 = iVar2;
        if (local_8 == -1) {
          *param_10 = -1;
          tlog(1,"Variable not declared");
          fVar3 = (float10)-1.0;
          goto LAB_0050ee62;
        }
        *param_8 = 1;
        fVar3 = (float10)*param_9;
        goto LAB_0050ee60;
      }
    }
    *param_8 = 0;
    _ftol2_sse();
    *param_9 = extraout_EAX_00;
    fVar3 = extraout_ST0;
  }
LAB_0050ee60:
  *param_2 = *param_2 + 1;
LAB_0050ee62:
  return (double)fVar3;
}
