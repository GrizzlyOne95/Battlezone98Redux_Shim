/*
 * Entry: 0050ed4b
 * Name: negation
 * Namespace: Global
 * Signature: double negation(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
negation(_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,char (*param_6) [80]
        ,int *param_7,int *param_8,int *param_9,int *param_10)

{
  int extraout_EAX;
  bool bVar1;
  float10 fVar2;
  float10 extraout_ST0;
  
  bVar1 = param_6[*param_2][0] == '-';
  if (bVar1) {
    *param_2 = *param_2 + 1;
  }
  parentheses(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  if (*param_8 == 0) {
    _ftol2_sse();
    *param_9 = extraout_EAX;
    fVar2 = extraout_ST0;
  }
  else {
    if (bVar1) {
      *param_9 = -*param_9;
    }
    fVar2 = (float10)*param_9;
  }
  return (double)fVar2;
}
