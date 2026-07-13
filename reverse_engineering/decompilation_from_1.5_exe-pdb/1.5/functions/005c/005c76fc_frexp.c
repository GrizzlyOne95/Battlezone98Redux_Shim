/*
 * Entry: 005c76fc
 * Name: frexp
 * Namespace: Global
 * Signature: undefined frexp()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* frexp */

float10 __cdecl frexp(double param_1,int *param_2)

{
  double dVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c76fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  dVar1 = frexp(param_1,param_2);
  return (float10)dVar1;
}
