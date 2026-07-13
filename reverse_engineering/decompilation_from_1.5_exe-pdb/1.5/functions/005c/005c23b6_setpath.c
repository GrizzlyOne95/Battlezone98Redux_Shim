/*
 * Entry: 005c23b6
 * Name: setpath
 * Namespace: Global
 * Signature: void setpath(lua_State * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl setpath(lua_State *param_1,char *param_2,char *param_3,char *param_4)

{
  lua_State *in_EAX;
  char *pcVar1;
  lua_State *unaff_EDI;
  
  pcVar1 = getenv(param_2);
  if (pcVar1 == (char *)0x0) {
    lua_pushstring(in_EAX,param_3);
  }
  else {
    pcVar1 = luaL_gsub(in_EAX,pcVar1,";;",";\x01;");
    luaL_gsub(in_EAX,pcVar1,"\x01",param_3);
    lua_remove(in_EAX,-2);
  }
  setprogdir(unaff_EDI);
  lua_setfield(in_EAX,-2,(char *)param_1);
  return;
}
