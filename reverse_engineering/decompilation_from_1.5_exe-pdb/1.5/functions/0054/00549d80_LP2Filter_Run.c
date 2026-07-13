/*
 * Entry: 00549d80
 * Name: LP2Filter_Run
 * Namespace: Global
 * Signature: float LP2Filter_Run(LP2_FILTER * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl LP2Filter_Run(LP2_FILTER *param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = ((float10)param_2 * (float10)param_1->b0 - (float10)param_1->my1 * (float10)param_1->a1) -
          (float10)param_1->a2 * (float10)param_1->my2;
  param_1->my2 = param_1->my1;
  param_1->my1 = (double)fVar1;
  return (float)fVar1;
}
