/*
 * Entry: 005ad7c0
 * Name: drft_backward
 * Namespace: Global
 * Signature: void drft_backward(drft_lookup * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drft_backward(drft_lookup *param_1,float *param_2)

{
  int iVar1;
  int *unaff_ESI;
  
  iVar1 = param_1->n;
  if (iVar1 != 1) {
    drftb1(iVar1,param_2,param_1->trigcache,param_1->trigcache + iVar1,unaff_ESI);
  }
  return;
}
