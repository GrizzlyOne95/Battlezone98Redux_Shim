/*
 * Entry: 005c2a28
 * Name: luaB_collectgarbage
 * Namespace: Global
 * Signature: int luaB_collectgarbage(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_collectgarbage(lua_State *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 unaff_EDI;
  
  iVar2 = luaL_checkoption(param_1,1,"collect",opts);
  iVar3 = luaL_optinteger(param_1,2,0);
  iVar3 = lua_gc(param_1,optsnum[iVar2],iVar3);
  iVar2 = optsnum[iVar2];
  if (iVar2 == 3) {
    iVar2 = lua_gc(param_1,4,0);
    uVar1 = (undefined4)((ulonglong)((double)iVar2 * 0.0009765625 + (double)iVar3) >> 0x20);
  }
  else {
    if (iVar2 == 5) {
      lua_pushboolean(param_1,iVar3);
      return 1;
    }
    uVar1 = (undefined4)((ulonglong)(double)iVar3 >> 0x20);
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,uVar1));
  return 1;
}
