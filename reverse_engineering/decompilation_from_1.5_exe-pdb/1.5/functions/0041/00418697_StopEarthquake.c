/*
 * Entry: 00418697
 * Name: StopEarthquake
 * Namespace: Global
 * Signature: int StopEarthquake(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopEarthquake(lua_State *param_1)

{
  EarthQuake::StopQuake(&earthQuake);
  return 0;
}
