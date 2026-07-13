/*
 * Entry: 005b62f0
 * Name: lua_pushvfstring
 * Namespace: Global
 * Signature: char * lua_pushvfstring(lua_State * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_pushvfstring(lua_State *param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pcVar1 = luaO_pushvfstring(param_1,param_2,param_3);
  return pcVar1;
}
