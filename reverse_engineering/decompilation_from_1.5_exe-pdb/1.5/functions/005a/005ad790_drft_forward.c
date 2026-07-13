/*
 * Entry: 005ad790
 * Name: drft_forward
 * Namespace: Global
 * Signature: void drft_forward(drft_lookup * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drft_forward(drft_lookup *param_1,float *param_2)

{
  int iVar1;
  float *unaff_ESI;
  int *unaff_retaddr;
  
  iVar1 = param_1->n;
  if (iVar1 != 1) {
    drftf1(iVar1,param_1->trigcache,param_1->trigcache + iVar1,unaff_ESI,unaff_retaddr);
  }
  return;
}
