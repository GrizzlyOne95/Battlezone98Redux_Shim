/*
 * Entry: 005c573d
 * Name: LoadDebug
 * Namespace: Global
 * Signature: void LoadDebug(LoadState * param_1, Proto * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadDebug(LoadState *param_1,Proto *param_2)

{
  int iVar1;
  LoadState *pLVar2;
  void *pvVar3;
  int iVar4;
  TString *pTVar5;
  undefined4 *unaff_EBX;
  LoadState *unaff_ESI;
  int unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = LoadInt(unaff_ESI);
  if (iVar1 + 1U < 0x40000000) {
    pLVar2 = luaM_realloc_((lua_State *)*unaff_EBX,(void *)0x0,0,iVar1 << 2);
  }
  else {
    pLVar2 = luaM_toobig((lua_State *)*unaff_EBX);
  }
  *(LoadState **)(unaff_EDI + 0x14) = pLVar2;
  *(int *)(unaff_EDI + 0x30) = iVar1;
  LoadBlock(pLVar2,(void *)(iVar1 << 2),(uint)unaff_ESI);
  local_c = LoadInt(unaff_ESI);
  if (local_c + 1U < 0x15555556) {
    pvVar3 = luaM_realloc_((lua_State *)*unaff_EBX,(void *)0x0,0,local_c * 0xc);
  }
  else {
    pvVar3 = luaM_toobig((lua_State *)*unaff_EBX);
  }
  *(void **)(unaff_EDI + 0x18) = pvVar3;
  *(int *)(unaff_EDI + 0x38) = local_c;
  if (0 < local_c) {
    iVar4 = 0;
    iVar1 = local_c;
    do {
      *(undefined4 *)(iVar4 + *(int *)(unaff_EDI + 0x18)) = 0;
      iVar4 = iVar4 + 0xc;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    if (0 < local_c) {
      local_8 = 0;
      do {
        pTVar5 = LoadString(unaff_ESI);
        *(TString **)(local_8 + *(int *)(unaff_EDI + 0x18)) = pTVar5;
        iVar1 = LoadInt(unaff_ESI);
        *(int *)(local_8 + 4 + *(int *)(unaff_EDI + 0x18)) = iVar1;
        iVar1 = LoadInt(unaff_ESI);
        *(int *)(local_8 + 8 + *(int *)(unaff_EDI + 0x18)) = iVar1;
        local_8 = local_8 + 0xc;
        local_c = local_c + -1;
      } while (local_c != 0);
    }
  }
  iVar1 = LoadInt(unaff_ESI);
  if (iVar1 + 1U < 0x40000000) {
    pvVar3 = luaM_realloc_((lua_State *)*unaff_EBX,(void *)0x0,0,iVar1 << 2);
  }
  else {
    pvVar3 = luaM_toobig((lua_State *)*unaff_EBX);
  }
  *(void **)(unaff_EDI + 0x1c) = pvVar3;
  iVar4 = 0;
  *(int *)(unaff_EDI + 0x24) = iVar1;
  if (0 < iVar1) {
    do {
      *(undefined4 *)(*(int *)(unaff_EDI + 0x1c) + iVar4 * 4) = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar1);
  }
  local_c = 0;
  if (0 < iVar1) {
    do {
      pTVar5 = LoadString(unaff_ESI);
      *(TString **)(*(int *)(unaff_EDI + 0x1c) + local_c * 4) = pTVar5;
      local_c = local_c + 1;
    } while (local_c < iVar1);
  }
  return;
}
