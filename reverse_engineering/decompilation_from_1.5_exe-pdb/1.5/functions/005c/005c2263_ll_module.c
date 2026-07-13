/*
 * Entry: 005c2263
 * Name: ll_module
 * Namespace: Global
 * Signature: int ll_module(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ll_module(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *unaff_ESI;
  lua_State *unaff_EDI;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar2 = lua_gettop(param_1);
  lua_getfield(param_1,-10000,"_LOADED");
  lua_getfield(param_1,iVar2 + 1,pcVar1);
  iVar3 = lua_type(param_1,-1);
  if (iVar3 != 5) {
    lua_settop(param_1,-2);
    pcVar4 = luaL_findtable(param_1,-0x2712,pcVar1,1);
    if (pcVar4 != (char *)0x0) {
      iVar2 = luaL_error(param_1,"name conflict for module \'%s\'");
      return iVar2;
    }
    lua_pushvalue(param_1,-1);
    lua_setfield(param_1,iVar2 + 1,pcVar1);
  }
  lua_getfield(param_1,-1,"_NAME");
  iVar3 = lua_type(param_1,-1);
  if (iVar3 == 0) {
    lua_settop(param_1,-2);
    modinit(unaff_EDI,unaff_ESI);
  }
  else {
    lua_settop(param_1,-2);
  }
  lua_pushvalue(param_1,-1);
  setfenv(unaff_EDI);
  iVar3 = 2;
  if (1 < iVar2) {
    do {
      lua_pushvalue(param_1,iVar3);
      lua_pushvalue(param_1,-2);
      lua_call(param_1,1,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar2);
  }
  return 0;
}
