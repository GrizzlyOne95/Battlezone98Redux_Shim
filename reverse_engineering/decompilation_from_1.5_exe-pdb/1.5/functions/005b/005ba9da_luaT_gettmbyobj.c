/*
 * Entry: 005ba9da
 * Name: luaT_gettmbyobj
 * Namespace: Global
 * Signature: lua_TValue * luaT_gettmbyobj(lua_State * param_1, lua_TValue * param_2, TMS param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaT_gettmbyobj(lua_State *param_1,lua_TValue *param_2,TMS param_3)

{
  int iVar1;
  Table *pTVar2;
  lua_TValue *plVar3;
  
  iVar1 = param_2->tt;
  if ((iVar1 == 5) || (iVar1 == 7)) {
    pTVar2 = *(Table **)((param_2->value).b + 8);
  }
  else {
    pTVar2 = param_1->l_G->mt[iVar1];
  }
  if (pTVar2 != (Table *)0x0) {
    plVar3 = luaH_getstr(pTVar2,param_1->l_G->tmname[param_3]);
    return plVar3;
  }
  return &luaO_nilobject_;
}
