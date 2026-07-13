/*
 * Entry: 005b77f7
 * Name: luaL_openlib
 * Namespace: Global
 * Signature: void luaL_openlib(lua_State * param_1, char * param_2, luaL_Reg * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_openlib(lua_State *param_1,char *param_2,luaL_Reg *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  luaL_Reg *plVar4;
  
  pcVar1 = param_2;
  if (param_2 != (char *)0x0) {
    param_2 = (char *)0x0;
    pcVar3 = param_3->name;
    plVar4 = param_3;
    while (pcVar3 != (char *)0x0) {
      param_2 = param_2 + 1;
      plVar4 = plVar4 + 1;
      pcVar3 = plVar4->name;
    }
    luaL_findtable(param_1,-10000,"_LOADED",1);
    lua_getfield(param_1,-1,pcVar1);
    iVar2 = lua_type(param_1,-1);
    if (iVar2 != 5) {
      lua_settop(param_1,-2);
      pcVar3 = luaL_findtable(param_1,-0x2712,pcVar1,(int)param_2);
      if (pcVar3 != (char *)0x0) {
        luaL_error(param_1,"name conflict for module \'%s\'");
      }
      lua_pushvalue(param_1,-1);
      lua_setfield(param_1,-3,pcVar1);
    }
    lua_remove(param_1,-2);
    lua_insert(param_1,-1 - param_4);
  }
  if (param_3->name != (char *)0x0) {
    plVar4 = param_3;
    do {
      if (0 < param_4) {
        param_3 = (luaL_Reg *)param_4;
        do {
          lua_pushvalue(param_1,-param_4);
          param_3 = (luaL_Reg *)((int)&param_3[-1].func + 3);
        } while (param_3 != (luaL_Reg *)0x0);
      }
      lua_pushcclosure(param_1,plVar4->func,param_4);
      lua_setfield(param_1,-2 - param_4,plVar4->name);
      plVar4 = plVar4 + 1;
    } while (plVar4->name != (char *)0x0);
  }
  lua_settop(param_1,-1 - param_4);
  return;
}
