/*
 * Entry: 005c1ec8
 * Name: loader_Croot
 * Namespace: Global
 * Signature: int loader_Croot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl loader_Croot(lua_State *param_1)

{
  char *pcVar1;
  char *pcVar2;
  lua_State *plVar3;
  int iVar4;
  char *unaff_EDI;
  lua_State *plVar5;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  pcVar2 = strchr(pcVar1,0x2e);
  iVar4 = 0;
  if (pcVar2 != (char *)0x0) {
    lua_pushlstring(param_1,pcVar1,(int)pcVar2 - (int)pcVar1);
    pcVar1 = "cpath";
    plVar3 = (lua_State *)lua_tolstring(param_1,-1,(uint *)0x0);
    plVar3 = (lua_State *)findfile(plVar3,pcVar1,unaff_EDI);
    if (plVar3 != (lua_State *)0x0) {
      plVar5 = param_1;
      pcVar1 = mkfuncname(param_1,unaff_EDI);
      iVar4 = ll_loadfunc(plVar3,pcVar1,(char *)plVar5);
      if (iVar4 != 0) {
        if (iVar4 != 2) {
          loaderror(param_1,(char *)plVar3);
        }
        lua_pushfstring(param_1,"\n\tno module \'%s\' in file \'%s\'");
      }
    }
    iVar4 = 1;
  }
  return iVar4;
}
