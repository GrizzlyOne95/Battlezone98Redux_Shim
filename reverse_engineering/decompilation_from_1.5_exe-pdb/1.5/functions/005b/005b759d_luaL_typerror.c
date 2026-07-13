/*
 * Entry: 005b759d
 * Name: luaL_typerror
 * Namespace: Global
 * Signature: int luaL_typerror(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_typerror(lua_State *param_1,int param_2,char *param_3)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = lua_type(param_1,param_2);
  lua_typename(param_1,iVar1);
  pcVar2 = lua_pushfstring(param_1,"%s expected, got %s");
  iVar1 = luaL_argerror(param_1,param_2,pcVar2);
  return iVar1;
}
