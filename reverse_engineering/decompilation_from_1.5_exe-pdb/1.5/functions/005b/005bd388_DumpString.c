/*
 * Entry: 005bd388
 * Name: DumpString
 * Namespace: Global
 * Signature: void DumpString(TString * param_1, DumpState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpString(TString *param_1,DumpState *param_2)

{
  int in_EAX;
  DumpState *unaff_EDI;
  DumpState *pDVar1;
  lua_State *local_8;
  
  if ((in_EAX == 0) || ((void *)(in_EAX + 0x10) == (void *)0x0)) {
    local_8 = (lua_State *)0x0;
    DumpBlock(&local_8,4,unaff_EDI);
  }
  else {
    local_8 = (lua_State *)(*(int *)(in_EAX + 0xc) + 1);
    pDVar1 = (DumpState *)&local_8;
    DumpBlock(pDVar1,4,unaff_EDI);
    DumpBlock((void *)(in_EAX + 0x10),(uint)local_8,pDVar1);
  }
  return;
}
