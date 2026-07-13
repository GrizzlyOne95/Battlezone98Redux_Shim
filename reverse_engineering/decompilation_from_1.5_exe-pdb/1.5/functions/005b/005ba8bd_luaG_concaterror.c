/*
 * Entry: 005ba8bd
 * Name: luaG_concaterror
 * Namespace: Global
 * Signature: void luaG_concaterror(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaG_concaterror(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  if ((param_2->tt == 4) || (param_2->tt == 3)) {
    param_2 = param_3;
  }
  luaG_typeerror(param_1,param_2,"concatenate");
  return;
}
