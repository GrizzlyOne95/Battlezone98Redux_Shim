/*
 * Entry: 005ad7f0
 * Name: drft_init
 * Namespace: Global
 * Signature: void drft_init(drft_lookup * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drft_init(drft_lookup *param_1,int param_2)

{
  float *pfVar1;
  int *piVar2;
  
  param_1->n = param_2;
  pfVar1 = calloc(param_2 * 3,4);
  param_1->trigcache = pfVar1;
  piVar2 = calloc(0x20,4);
  param_1->splitcache = piVar2;
  if (param_2 != 1) {
    drfti1(param_2,param_1->trigcache + param_2,piVar2);
  }
  return;
}
