/*
 * Entry: 005c1e79
 * Name: loader_C
 * Namespace: Global
 * Signature: int loader_C(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl loader_C(lua_State *param_1)

{
  lua_State *plVar1;
  lua_State *plVar2;
  char *pcVar3;
  int iVar4;
  char *unaff_EDI;
  
  plVar2 = param_1;
  plVar1 = (lua_State *)luaL_checklstring(param_1,1,(uint *)0x0);
  plVar2 = (lua_State *)findfile(plVar1,"cpath",(char *)plVar2);
  if (plVar2 != (lua_State *)0x0) {
    plVar1 = param_1;
    pcVar3 = mkfuncname(param_1,unaff_EDI);
    iVar4 = ll_loadfunc(plVar2,pcVar3,(char *)plVar1);
    if (iVar4 != 0) {
      loaderror(param_1,(char *)plVar2);
    }
  }
  return 1;
}
