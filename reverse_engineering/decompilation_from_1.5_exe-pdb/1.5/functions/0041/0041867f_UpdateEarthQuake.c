/*
 * Entry: 0041867f
 * Name: UpdateEarthQuake
 * Namespace: Global
 * Signature: int UpdateEarthQuake(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UpdateEarthQuake(lua_State *param_1)

{
  double dVar1;
  
  dVar1 = luaL_checknumber(param_1,1);
  UpdateEarthQuake((float)dVar1);
  return 0;
}
