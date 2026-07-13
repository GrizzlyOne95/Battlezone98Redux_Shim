/*
 * Entry: 005b776a
 * Name: luaL_optnumber
 * Namespace: Global
 * Signature: double luaL_optnumber(lua_State * param_1, int param_2, double param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl luaL_optnumber(lua_State *param_1,int param_2,double param_3)

{
  int iVar1;
  double dVar2;
  
  iVar1 = lua_type(param_1,param_2);
  if (iVar1 < 1) {
    return param_3;
  }
  dVar2 = luaL_checknumber(param_1,param_2);
  return dVar2;
}
