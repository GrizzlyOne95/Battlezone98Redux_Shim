/*
 * Entry: 00418667
 * Name: StartEarthquake
 * Namespace: Global
 * Signature: int StartEarthquake(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StartEarthquake(lua_State *param_1)

{
  double dVar1;
  
  dVar1 = luaL_checknumber(param_1,1);
  StartEarthquake((float)dVar1);
  return 0;
}
