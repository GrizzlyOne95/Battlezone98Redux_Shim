/*
 * Entry: 005b631a
 * Name: lua_pushfstring
 * Namespace: Global
 * Signature: char * lua_pushfstring(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_pushfstring(lua_State *param_1,char *param_2)

{
  char *pcVar1;
  
  if (param_1->l_G->GCthreshold <= param_1->l_G->totalbytes) {
    luaC_step(param_1);
  }
  pcVar1 = luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  return pcVar1;
}
