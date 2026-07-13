/*
 * Entry: 005bd331
 * Name: DumpChar
 * Namespace: Global
 * Signature: void DumpChar(int param_1, DumpState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpChar(int param_1,DumpState *param_2)

{
  undefined1 uVar1;
  DumpState *unaff_EBP;
  
  uVar1 = (undefined1)param_1;
  param_1 = CONCAT13(uVar1,(undefined3)param_1);
  DumpBlock((void *)((int)&param_1 + 3),1,unaff_EBP);
  return;
}
