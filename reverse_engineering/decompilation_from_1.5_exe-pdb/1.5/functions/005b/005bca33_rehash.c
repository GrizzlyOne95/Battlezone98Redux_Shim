/*
 * Entry: 005bca33
 * Name: rehash
 * Namespace: Global
 * Signature: void rehash(lua_State * param_1, Table * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl rehash(lua_State *param_1,Table *param_2,lua_TValue *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int unaff_EBX;
  int iVar5;
  int *unaff_EDI;
  lua_TValue *plVar6;
  Table *pTVar7;
  lua_TValue local_80 [6];
  lua_TValue *local_14;
  int local_10;
  Table *local_c;
  int local_8;
  
  iVar5 = *(int *)(unaff_EBX + 0x1c);
  local_14 = (lua_TValue *)0x0;
  plVar6 = local_80;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    (plVar6->value).gc = (GCObject *)0x0;
    plVar6 = (lua_TValue *)((int)&plVar6->value + 4);
  }
  iVar2 = 1;
  local_c = (Table *)0x0;
  local_8 = 1;
  do {
    local_10 = 0;
    iVar1 = iVar2;
    if ((iVar5 < iVar2) && (iVar1 = iVar5, iVar5 < local_8)) break;
    iVar3 = 0;
    if (local_8 <= iVar1) {
      iVar3 = local_8 * 0x10;
      iVar1 = (iVar1 - local_8) + 1;
      local_8 = local_8 + iVar1;
      piVar4 = (int *)(iVar3 + -8 + *(int *)(unaff_EBX + 0xc));
      do {
        if (*piVar4 != 0) {
          local_10 = local_10 + 1;
        }
        piVar4 = piVar4 + 4;
        iVar1 = iVar1 + -1;
        iVar3 = local_10;
      } while (iVar1 != 0);
    }
    local_14 = (lua_TValue *)((int)&local_14->value + iVar3);
    piVar4 = (int *)((int)&local_80[0].value + (int)local_c * 4);
    *piVar4 = *piVar4 + iVar3;
    local_c = (Table *)((int)local_c + 1);
    iVar2 = iVar2 * 2;
  } while ((int)local_c < 0x1b);
  iVar5 = 1 << (*(byte *)(unaff_EBX + 7) & 0x1f);
  iVar2 = 0;
  local_10 = 0;
  if (iVar5 != 0) {
    local_c = (Table *)(iVar5 << 5);
    do {
      local_c = (Table *)((int)local_c + -0x20);
      iVar5 = iVar5 + -1;
      if (*(int *)(*(int *)(unaff_EBX + 0x10) + (int)local_c + 8) != 0) {
        iVar1 = countint(local_80,unaff_EDI);
        local_10 = local_10 + iVar1;
        iVar2 = iVar2 + 1;
      }
    } while (iVar5 != 0);
  }
  iVar5 = countint(local_80,unaff_EDI);
  plVar6 = local_14;
  iVar5 = (int)&local_14->value + iVar5 + local_10;
  pTVar7 = (Table *)0x1;
  local_8 = 0;
  local_10 = 0;
  local_c = (Table *)0x0;
  if (0 < iVar5) {
    local_14 = local_80;
    do {
      if ((0 < (local_14->value).b) &&
         (local_8 = local_8 + (local_14->value).b, (int)pTVar7 / 2 < local_8)) {
        local_10 = local_8;
        local_c = pTVar7;
      }
      if (local_8 == iVar5) break;
      local_14 = (lua_TValue *)((int)&local_14->value + 4);
      pTVar7 = (Table *)((int)pTVar7 * 2);
    } while ((int)pTVar7 / 2 < iVar5);
  }
  resize(param_1,local_c,(int)plVar6 + ((iVar2 + 1) - local_10),(int)unaff_EDI);
  return;
}
