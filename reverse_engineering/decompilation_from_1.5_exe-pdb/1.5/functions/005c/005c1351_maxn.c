/*
 * Entry: 005c1351
 * Name: maxn
 * Namespace: Global
 * Signature: int maxn(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl maxn(lua_State *param_1)

{
  int iVar1;
  undefined4 unaff_ESI;
  double dVar2;
  double local_c;
  
  local_c = 0.0;
  luaL_checktype(param_1,1,5);
  lua_pushnil(param_1);
  iVar1 = lua_next(param_1,1);
  while (iVar1 != 0) {
    lua_settop(param_1,-2);
    iVar1 = lua_type(param_1,-1);
    if ((iVar1 == 3) && (dVar2 = lua_tonumber(param_1,-1), local_c < dVar2)) {
      local_c = dVar2;
    }
    iVar1 = lua_next(param_1,1);
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,(int)((ulonglong)local_c >> 0x20)));
  return 1;
}
