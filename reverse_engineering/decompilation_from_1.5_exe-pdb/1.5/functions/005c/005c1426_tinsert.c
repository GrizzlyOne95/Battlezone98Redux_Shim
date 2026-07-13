/*
 * Entry: 005c1426
 * Name: tinsert
 * Namespace: Global
 * Signature: int tinsert(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl tinsert(lua_State *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  luaL_checktype(param_1,1,5);
  uVar1 = lua_objlen(param_1,1);
  iVar3 = uVar1 + 1;
  iVar2 = lua_gettop(param_1);
  local_8 = iVar3;
  if (iVar2 != 2) {
    if (iVar2 != 3) {
      iVar2 = luaL_error(param_1,"wrong number of arguments to \'insert\'");
      return iVar2;
    }
    local_8 = luaL_checkinteger(param_1,2);
    iVar2 = iVar3;
    if (local_8 > iVar3) {
      iVar2 = local_8;
    }
    if (iVar2 != local_8 && SBORROW4(iVar2,local_8) == (local_8 <= iVar3 && iVar3 - local_8 < 0)) {
      do {
        iVar3 = iVar2 + -1;
        lua_rawgeti(param_1,1,iVar3);
        lua_rawseti(param_1,1,iVar2);
        iVar2 = iVar3;
      } while (local_8 < iVar3);
    }
  }
  lua_rawseti(param_1,1,local_8);
  return 0;
}
