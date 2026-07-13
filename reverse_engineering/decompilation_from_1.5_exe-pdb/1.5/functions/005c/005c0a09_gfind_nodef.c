/*
 * Entry: 005c0a09
 * Name: gfind_nodef
 * Namespace: Global
 * Signature: int gfind_nodef(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl gfind_nodef(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_error(param_1,"\'string.gfind\' was renamed to \'string.gmatch\'");
  return iVar1;
}
