/*
 * Entry: 005b6e91
 * Name: luaL_findtable
 * Namespace: Global
 * Signature: char * luaL_findtable(lua_State * param_1, int param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaL_findtable(lua_State *param_1,int param_2,char *param_3,int param_4)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  lua_pushvalue(param_1,param_2);
  do {
    pcVar2 = strchr(param_3,0x2e);
    pcVar1 = param_3;
    if (pcVar2 == (char *)0x0) {
      do {
        pcVar2 = pcVar1;
        pcVar1 = pcVar2 + 1;
      } while (*pcVar2 != '\0');
    }
    lua_pushlstring(param_1,param_3,(int)pcVar2 - (int)param_3);
    lua_rawget(param_1,-2);
    iVar3 = lua_type(param_1,-1);
    if (iVar3 == 0) {
      lua_settop(param_1,-2);
      iVar3 = param_4;
      if (*pcVar2 == '.') {
        iVar3 = 1;
      }
      lua_createtable(param_1,0,iVar3);
      lua_pushlstring(param_1,param_3,(int)pcVar2 - (int)param_3);
      lua_pushvalue(param_1,-2);
      lua_settable(param_1,-4);
    }
    else {
      iVar3 = lua_type(param_1,-1);
      if (iVar3 != 5) {
        lua_settop(param_1,-3);
        return param_3;
      }
    }
    lua_remove(param_1,-2);
    param_3 = pcVar2 + 1;
  } while (*pcVar2 == '.');
  return (char *)0x0;
}
