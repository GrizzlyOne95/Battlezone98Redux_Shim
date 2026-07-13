/*
 * Entry: 005c1e2d
 * Name: mkfuncname
 * Namespace: Global
 * Signature: char * mkfuncname(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl mkfuncname(lua_State *param_1,char *param_2)

{
  char *in_EAX;
  char *pcVar1;
  
  pcVar1 = strchr(in_EAX,0x2d);
  if (pcVar1 != (char *)0x0) {
    in_EAX = pcVar1 + 1;
  }
  luaL_gsub(param_1,in_EAX,".","_");
  pcVar1 = lua_pushfstring(param_1,"luaopen_%s");
  lua_remove(param_1,-2);
  return pcVar1;
}
