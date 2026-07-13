/*
 * Entry: 005bcc41
 * Name: luaH_setstr
 * Namespace: Global
 * Signature: lua_TValue * luaH_setstr(lua_State * param_1, Table * param_2, TString * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaH_setstr(lua_State *param_1,Table *param_2,TString *param_3)

{
  lua_TValue *plVar1;
  Value local_14;
  undefined4 local_c;
  
  plVar1 = luaH_getstr(param_2,param_3);
  if (plVar1 == &luaO_nilobject_) {
    local_14.gc = (GCObject *)param_3;
    local_c = 4;
    plVar1 = newkey(param_1,param_2,(lua_TValue *)&local_14);
  }
  return plVar1;
}
