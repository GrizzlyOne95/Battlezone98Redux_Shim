/*
 * Entry: 005b7723
 * Name: luaL_checknumber
 * Namespace: Global
 * Signature: double luaL_checknumber(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl luaL_checknumber(lua_State *param_1,int param_2)

{
  int iVar1;
  double dVar2;
  
  dVar2 = lua_tonumber(param_1,param_2);
  if (dVar2 == 0.0) {
    iVar1 = lua_isnumber(param_1,param_2);
    if (iVar1 == 0) {
      tag_error(param_1,param_2,3);
    }
  }
  return dVar2;
}
