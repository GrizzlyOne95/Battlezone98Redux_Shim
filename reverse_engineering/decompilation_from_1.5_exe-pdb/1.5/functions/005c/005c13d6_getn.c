/*
 * Entry: 005c13d6
 * Name: getn
 * Namespace: Global
 * Signature: int getn(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl getn(lua_State *param_1)

{
  uint uVar1;
  
  luaL_checktype(param_1,1,5);
  uVar1 = lua_objlen(param_1,1);
  lua_pushinteger(param_1,uVar1);
  return 1;
}
