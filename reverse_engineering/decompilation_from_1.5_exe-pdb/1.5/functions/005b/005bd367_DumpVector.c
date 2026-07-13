/*
 * Entry: 005bd367
 * Name: DumpVector
 * Namespace: Global
 * Signature: void DumpVector(void * param_1, int param_2, uint param_3, DumpState * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpVector(void *param_1,int param_2,uint param_3,DumpState *param_4)

{
  DumpState *in_ECX;
  DumpState *unaff_EDI;
  DumpState *pDVar1;
  
  pDVar1 = in_ECX;
  DumpInt((int)in_ECX,unaff_EDI);
  DumpBlock(param_1,(int)in_ECX * param_2,pDVar1);
  return;
}
