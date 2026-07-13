/*
 * Entry: 005b816b
 * Name: luaO_pushfstring
 * Namespace: Global
 * Signature: char * luaO_pushfstring(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaO_pushfstring(lua_State *param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  return pcVar1;
}
