/*
 * Entry: 0050f5fd
 * Name: expression
 * Namespace: Global
 * Signature: double expression(_domain * param_1, int param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
expression(_domain *param_1,int param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  double dVar1;
  
  *param_10 = 0;
  if (param_3 < param_2) {
    *param_10 = -1;
    return 0.0;
  }
  dVar1 = equals_not_equals(param_1,&param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9
                            ,param_10);
  return dVar1;
}
