/*
 * Entry: 005ba916
 * Name: luaG_ordererror
 * Namespace: Global
 * Signature: int luaG_ordererror(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaG_ordererror(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  if (*(char *)(*(int *)(&luaT_typenames + param_2->tt * 4) + 2) ==
      *(char *)(*(int *)(&luaT_typenames + param_3->tt * 4) + 2)) {
    luaG_runerror(param_1,"attempt to compare two %s values");
  }
  else {
    luaG_runerror(param_1,"attempt to compare %s with %s");
  }
  return 0;
}
