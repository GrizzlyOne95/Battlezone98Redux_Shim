/*
 * Entry: 005bd349
 * Name: DumpInt
 * Namespace: Global
 * Signature: void DumpInt(int param_1, DumpState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpInt(int param_1,DumpState *param_2)

{
  DumpState *unaff_retaddr;
  
  DumpBlock(&param_1,4,unaff_retaddr);
  return;
}
