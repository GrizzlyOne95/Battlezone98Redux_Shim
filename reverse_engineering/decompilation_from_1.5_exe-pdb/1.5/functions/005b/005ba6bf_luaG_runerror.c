/*
 * Entry: 005ba6bf
 * Name: luaG_runerror
 * Namespace: Global
 * Signature: void luaG_runerror(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaG_runerror(lua_State *param_1,char *param_2)

{
  lua_State *plVar1;
  lua_State *plVar2;
  
  plVar2 = param_1;
  plVar1 = (lua_State *)luaO_pushvfstring(param_1,param_2,&stack0x0000000c);
  addinfo(plVar1,(char *)plVar2);
  luaG_errormsg(param_1);
  return;
}
