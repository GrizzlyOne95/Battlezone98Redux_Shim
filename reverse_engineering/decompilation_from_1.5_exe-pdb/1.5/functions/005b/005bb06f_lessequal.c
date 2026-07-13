/*
 * Entry: 005bb06f
 * Name: lessequal
 * Namespace: Global
 * Signature: int lessequal(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lessequal(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  lua_State *unaff_EBX;
  lua_State *unaff_ESI;
  lua_State *unaff_EDI;
  bool bVar3;
  TString *unaff_retaddr;
  
  plVar1 = unaff_EDI->top;
  if (plVar1 != unaff_ESI->top) {
LAB_005bb0d5:
    iVar2 = luaG_ordererror(unaff_EBX,(lua_TValue *)unaff_EDI,(lua_TValue *)unaff_ESI);
    return iVar2;
  }
  if (plVar1 == (lua_TValue *)0x3) {
    if (*(double *)unaff_ESI < *(double *)unaff_EDI) {
      return 0;
    }
    return 1;
  }
  if (plVar1 == (lua_TValue *)0x4) {
    iVar2 = l_strcmp(unaff_retaddr,(TString *)param_1);
    bVar3 = iVar2 < 1;
  }
  else {
    iVar2 = call_orderTM(unaff_EDI,(lua_TValue *)unaff_ESI,(lua_TValue *)0xe,(TMS)unaff_retaddr);
    if (iVar2 != -1) {
      return iVar2;
    }
    iVar2 = call_orderTM(unaff_ESI,(lua_TValue *)unaff_EDI,(lua_TValue *)0xd,(TMS)unaff_retaddr);
    if (iVar2 == -1) goto LAB_005bb0d5;
    bVar3 = iVar2 == 0;
  }
  return (uint)bVar3;
}
