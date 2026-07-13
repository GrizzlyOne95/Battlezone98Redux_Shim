/*
 * Entry: 00417f34
 * Name: GetRidOfSomeScrap
 * Namespace: Global
 * Signature: int GetRidOfSomeScrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetRidOfSomeScrap(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_optinteger(param_1,1,300);
  GetRidOfSomeScrap(iVar1);
  return 0;
}
