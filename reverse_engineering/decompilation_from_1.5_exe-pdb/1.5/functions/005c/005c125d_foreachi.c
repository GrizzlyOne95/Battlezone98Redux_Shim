/*
 * Entry: 005c125d
 * Name: foreachi
 * Namespace: Global
 * Signature: int foreachi(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl foreachi(lua_State *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  luaL_checktype(param_1,1,5);
  uVar1 = lua_objlen(param_1,1);
  luaL_checktype(param_1,2,6);
  if (0 < (int)uVar1) {
    do {
      lua_pushvalue(param_1,2);
      lua_pushinteger(param_1,iVar3);
      lua_rawgeti(param_1,1,iVar3);
      lua_call(param_1,2,1);
      iVar2 = lua_type(param_1,-1);
      if (iVar2 != 0) {
        return 1;
      }
      lua_settop(param_1,-2);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)uVar1);
  }
  return 0;
}
