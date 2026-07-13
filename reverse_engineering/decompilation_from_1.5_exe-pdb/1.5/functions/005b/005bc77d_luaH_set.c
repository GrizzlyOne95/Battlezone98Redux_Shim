/*
 * Entry: 005bc77d
 * Name: luaH_set
 * Namespace: Global
 * Signature: lua_TValue * luaH_set(lua_State * param_1, Table * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x005bc7bc) */

lua_TValue * __cdecl luaH_set(lua_State *param_1,Table *param_2,lua_TValue *param_3)

{
  lua_TValue *plVar1;
  
  plVar1 = luaH_get(param_2,param_3);
  param_2->flags = '\0';
  if (plVar1 == &luaO_nilobject_) {
    if (param_3->tt == 0) {
      luaG_runerror(param_1,"table index is nil");
    }
    plVar1 = newkey(param_1,param_2,param_3);
  }
  return plVar1;
}
