/*
 * Entry: 005bc7dc
 * Name: luaH_setnum
 * Namespace: Global
 * Signature: lua_TValue * luaH_setnum(lua_State * param_1, Table * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaH_setnum(lua_State *param_1,Table *param_2,int param_3)

{
  lua_TValue *plVar1;
  Value local_14;
  undefined4 local_c;
  
  plVar1 = luaH_getnum(param_2,param_3);
  if (plVar1 == &luaO_nilobject_) {
    local_14.n = (double)param_3;
    local_c = 3;
    plVar1 = newkey(param_1,param_2,(lua_TValue *)&local_14);
  }
  return plVar1;
}
