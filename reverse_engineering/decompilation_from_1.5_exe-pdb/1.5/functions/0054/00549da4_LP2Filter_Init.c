/*
 * Entry: 00549da4
 * Name: LP2Filter_Init
 * Namespace: Global
 * Signature: void LP2Filter_Init(LP2_FILTER * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LP2Filter_Init(LP2_FILTER *param_1,float param_2,float param_3)

{
  LP2_FILTER *extraout_ECX;
  int extraout_EDX;
  float10 fVar1;
  float fVar2;
  
  if (param_3 < 4.0) {
    param_3 = 4.0;
  }
  param_1->b0 = 1.0;
  fVar1 = (float10)fcos((float10)6.2831855 / (float10)param_3);
  param_1->a1 = (double)(fVar1 * (float10)param_2 * (float10)-2.0);
  param_1->a2 = (double)(param_2 * param_2);
  param_1->my1 = 0.0;
  param_1->my2 = 0.0;
  do {
    fVar2 = LP2Filter_Run(param_1,1.0);
    param_1 = extraout_ECX;
  } while (extraout_EDX != 1);
  extraout_ECX->b0 = (double)(1.0 / fVar2);
  extraout_ECX->my1 = 0.0;
  extraout_ECX->my2 = 0.0;
  return;
}
