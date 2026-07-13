/*
 * Entry: 005b6f8f
 * Name: adjuststack
 * Namespace: Global
 * Signature: void adjuststack(luaL_Buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl adjuststack(luaL_Buffer *param_1)

{
  lua_State *plVar1;
  uint uVar2;
  int unaff_ESI;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar3 = 1;
  if (1 < *(int *)(unaff_ESI + 4)) {
    plVar1 = *(lua_State **)(unaff_ESI + 8);
    local_8 = lua_objlen(plVar1,-1);
    local_c = -2;
    do {
      uVar2 = lua_objlen(plVar1,local_c);
      if (((*(int *)(unaff_ESI + 4) - iVar3) + 1 < 10) && (local_8 <= uVar2)) break;
      local_8 = local_8 + uVar2;
      iVar3 = iVar3 + 1;
      local_c = local_c + -1;
    } while (iVar3 < *(int *)(unaff_ESI + 4));
    lua_concat(plVar1,iVar3);
    *(int *)(unaff_ESI + 4) = *(int *)(unaff_ESI + 4) + (1 - iVar3);
  }
  return;
}
