/*
 * Entry: 005c1ded
 * Name: loader_Lua
 * Namespace: Global
 * Signature: int loader_Lua(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl loader_Lua(lua_State *param_1)

{
  lua_State *plVar1;
  char *pcVar2;
  int iVar3;
  lua_State *plVar4;
  
  plVar4 = param_1;
  plVar1 = (lua_State *)luaL_checklstring(param_1,1,(uint *)0x0);
  pcVar2 = findfile(plVar1,"path",(char *)plVar4);
  if (pcVar2 != (char *)0x0) {
    iVar3 = luaL_loadfile(param_1,pcVar2);
    if (iVar3 != 0) {
      loaderror(param_1,pcVar2);
    }
  }
  return 1;
}
