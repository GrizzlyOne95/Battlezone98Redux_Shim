/*
 * Entry: 005bf935
 * Name: math_max
 * Namespace: Global
 * Signature: int math_max(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_max(lua_State *param_1)

{
  int iVar1;
  undefined4 unaff_EDI;
  int iVar2;
  double dVar3;
  double local_c;
  
  iVar1 = lua_gettop(param_1);
  local_c = luaL_checknumber(param_1,1);
  iVar2 = 2;
  if (1 < iVar1) {
    do {
      dVar3 = luaL_checknumber(param_1,iVar2);
      if (local_c < dVar3) {
        local_c = dVar3;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 <= iVar1);
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)local_c >> 0x20)));
  return 1;
}
