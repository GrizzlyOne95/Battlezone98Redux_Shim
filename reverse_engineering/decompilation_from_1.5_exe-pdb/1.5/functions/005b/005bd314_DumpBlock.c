/*
 * Entry: 005bd314
 * Name: DumpBlock
 * Namespace: Global
 * Signature: void DumpBlock(void * param_1, uint param_2, DumpState * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpBlock(void *param_1,uint param_2,DumpState *param_3)

{
  undefined4 uVar1;
  undefined4 *unaff_ESI;
  
  if (unaff_ESI[4] == 0) {
    uVar1 = (*(code *)unaff_ESI[1])(*unaff_ESI,param_1,param_2,unaff_ESI[2]);
    unaff_ESI[4] = uVar1;
  }
  return;
}
