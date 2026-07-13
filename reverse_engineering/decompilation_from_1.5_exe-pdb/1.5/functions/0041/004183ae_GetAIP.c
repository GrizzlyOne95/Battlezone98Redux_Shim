/*
 * Entry: 004183ae
 * Name: GetAIP
 * Namespace: Global
 * Signature: int GetAIP(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetAIP(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = luaL_optinteger(param_1,1,2);
  pcVar2 = GetAIP(iVar1);
  if (pcVar2 != (char *)0x0) {
    lua_pushstring(param_1,pcVar2);
    return 1;
  }
  return 0;
}
