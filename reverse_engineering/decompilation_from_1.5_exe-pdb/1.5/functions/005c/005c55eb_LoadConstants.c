/*
 * Entry: 005c55eb
 * Name: LoadConstants
 * Namespace: Global
 * Signature: void LoadConstants(LoadState * param_1, Proto * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadConstants(LoadState *param_1,Proto *param_2)

{
  Mbuffer *pMVar1;
  void *pvVar2;
  int iVar3;
  TString *pTVar4;
  int iVar5;
  Proto *pPVar6;
  Mbuffer *pMVar7;
  int unaff_EBX;
  int iVar8;
  LoadState *unaff_EDI;
  uint *puVar9;
  LoadState local_14;
  
  pMVar1 = (Mbuffer *)LoadInt(unaff_EDI);
  if ((undefined1 *)((int)&pMVar1->buffer + 1U) < (undefined1 *)0x10000000) {
    pvVar2 = luaM_realloc_(param_1->L,(void *)0x0,0,(int)pMVar1 << 4);
  }
  else {
    pvVar2 = luaM_toobig(param_1->L);
  }
  *(void **)(unaff_EBX + 8) = pvVar2;
  *(Mbuffer **)(unaff_EBX + 0x28) = pMVar1;
  if (0 < (int)pMVar1) {
    iVar3 = 0;
    pMVar7 = pMVar1;
    do {
      *(undefined4 *)(iVar3 + 8 + *(int *)(unaff_EBX + 8)) = 0;
      iVar3 = iVar3 + 0x10;
      pMVar7 = (Mbuffer *)((int)&pMVar7[-1].buffsize + 3);
    } while (pMVar7 != (Mbuffer *)0x0);
    if (0 < (int)pMVar1) {
      local_14.name = (char *)0x0;
      local_14.b = pMVar1;
      do {
        puVar9 = (uint *)(local_14.name + *(int *)(unaff_EBX + 8));
        iVar3 = LoadChar(param_1);
        if (iVar3 == 0) {
          puVar9[2] = 0;
        }
        else if (iVar3 == 1) {
          iVar3 = LoadChar(param_1);
          *puVar9 = (uint)(iVar3 != 0);
          puVar9[2] = 1;
        }
        else if (iVar3 == 3) {
          LoadBlock(&local_14,(void *)0x8,(uint)unaff_EDI);
          puVar9[0] = (uint)local_14.L;
          puVar9[1] = (uint)local_14.Z;
          puVar9[2] = 3;
        }
        else if (iVar3 == 4) {
          pTVar4 = LoadString(unaff_EDI);
          *puVar9 = (uint)pTVar4;
          puVar9[2] = 4;
        }
        else {
          error((LoadState *)"bad constant",(char *)unaff_EDI);
        }
        local_14.name = local_14.name + 0x10;
        local_14.b = (Mbuffer *)((int)&local_14.b[-1].buffsize + 3);
      } while (local_14.b != (Mbuffer *)0x0);
    }
  }
  iVar3 = LoadInt(unaff_EDI);
  if (iVar3 + 1U < 0x40000000) {
    pvVar2 = luaM_realloc_(param_1->L,(void *)0x0,0,iVar3 << 2);
  }
  else {
    pvVar2 = luaM_toobig(param_1->L);
  }
  *(void **)(unaff_EBX + 0x10) = pvVar2;
  iVar8 = 0;
  iVar5 = 0;
  *(int *)(unaff_EBX + 0x34) = iVar3;
  if (0 < iVar3) {
    do {
      *(undefined4 *)(*(int *)(unaff_EBX + 0x10) + iVar5 * 4) = 0;
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar3);
    if (0 < iVar3) {
      do {
        pPVar6 = LoadFunction(param_1,*(TString **)(unaff_EBX + 0x20));
        *(Proto **)(*(int *)(unaff_EBX + 0x10) + iVar8 * 4) = pPVar6;
        iVar8 = iVar8 + 1;
      } while (iVar8 < iVar3);
    }
  }
  return;
}
