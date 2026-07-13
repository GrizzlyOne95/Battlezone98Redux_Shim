/*
 * Entry: 0050f4f4
 * Name: parentheses
 * Namespace: Global
 * Signature: double parentheses(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
parentheses(_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,
           char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  int iVar1;
  int iVar2;
  int extraout_EAX;
  double dVar3;
  char *pcVar4;
  
  iVar1 = *param_2;
  if (param_6[iVar1][0] == '(') {
    *param_2 = iVar1 + 1;
    iVar2 = check_type_cast(param_6[iVar1 + 1]);
    if (iVar2 == 0) {
      dVar3 = equals_not_equals(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,param_10);
      if (param_6[*param_2][0] == ')') {
        *param_2 = *param_2 + 1;
        return dVar3;
      }
      pcVar4 = "Unmatched parentheses\n";
    }
    else {
      *param_2 = iVar1 + 2;
      if (param_6[iVar1 + 2][0] == ')') {
        *param_2 = iVar1 + 3;
        dVar3 = negation(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
        if (iVar2 != 1) {
          *param_8 = 0;
          return dVar3;
        }
        *param_8 = 1;
        _ftol2_sse();
        return (double)extraout_EAX;
      }
      pcVar4 = "Unmatched parenthesis in type-casting\n";
    }
    tlog(1,pcVar4);
    dVar3 = -1.0;
  }
  else {
    dVar3 = constant_or_variable
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       param_10);
  }
  return dVar3;
}
