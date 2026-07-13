/*
 * Entry: 005c14b4
 * Name: tremove
 * Namespace: Global
 * Signature: int tremove(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl tremove(lua_State *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  luaL_checktype(param_1,1,5);
  uVar1 = lua_objlen(param_1,1);
  iVar2 = luaL_optinteger(param_1,2,uVar1);
  if ((iVar2 < 1) || ((int)uVar1 < iVar2)) {
    iVar3 = 0;
  }
  else {
    lua_rawgeti(param_1,1,iVar2);
    while (iVar2 < (int)uVar1) {
      lua_rawgeti(param_1,1,iVar2 + 1);
      lua_rawseti(param_1,1,iVar2);
      iVar2 = iVar2 + 1;
    }
    lua_pushnil(param_1);
    lua_rawseti(param_1,1,uVar1);
  }
  return iVar3;
}
