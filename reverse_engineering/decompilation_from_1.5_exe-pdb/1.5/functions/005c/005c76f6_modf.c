/*
 * Entry: 005c76f6
 * Name: modf
 * Namespace: Global
 * Signature: undefined modf()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* modf */

float10 __cdecl modf(double param_1,double *param_2)

{
  double dVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c76f6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  dVar1 = modf(param_1,param_2);
  return (float10)dVar1;
}
