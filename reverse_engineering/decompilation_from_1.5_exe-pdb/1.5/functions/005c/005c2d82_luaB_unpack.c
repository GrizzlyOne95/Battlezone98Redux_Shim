/*
 * Entry: 005c2d82
 * Name: luaB_unpack
 * Namespace: Global
 * Signature: int luaB_unpack(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_unpack(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  luaL_checktype(param_1,1,5);
  iVar1 = luaL_optinteger(param_1,2,1);
  iVar2 = lua_type(param_1,3);
  if (iVar2 < 1) {
    uVar3 = lua_objlen(param_1,1);
  }
  else {
    uVar3 = luaL_checkinteger(param_1,3);
  }
  if ((int)uVar3 < iVar1) {
    iVar2 = 0;
  }
  else {
    iVar2 = (uVar3 - iVar1) + 1;
    if ((iVar2 < 1) || (iVar4 = lua_checkstack(param_1,iVar2), iVar4 == 0)) {
      iVar2 = luaL_error(param_1,"too many results to unpack");
    }
    else {
      for (; lua_rawgeti(param_1,1,iVar1), iVar1 < (int)uVar3; iVar1 = iVar1 + 1) {
      }
    }
  }
  return iVar2;
}
