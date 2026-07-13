/*
 * Entry: 005c55a1
 * Name: LoadCode
 * Namespace: Global
 * Signature: void LoadCode(LoadState * param_1, Proto * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadCode(LoadState *param_1,Proto *param_2)

{
  int iVar1;
  LoadState *pLVar2;
  int unaff_EBX;
  LoadState *unaff_ESI;
  undefined4 *unaff_EDI;
  
  iVar1 = LoadInt(unaff_ESI);
  if (iVar1 + 1U < 0x40000000) {
    pLVar2 = luaM_realloc_((lua_State *)*unaff_EDI,(void *)0x0,0,iVar1 << 2);
  }
  else {
    pLVar2 = luaM_toobig((lua_State *)*unaff_EDI);
  }
  *(LoadState **)(unaff_EBX + 0xc) = pLVar2;
  *(int *)(unaff_EBX + 0x2c) = iVar1;
  LoadBlock(pLVar2,(void *)(iVar1 << 2),(uint)unaff_ESI);
  return;
}
