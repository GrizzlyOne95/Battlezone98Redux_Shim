/*
 * Entry: 00418652
 * Name: GetCockpitTimer
 * Namespace: Global
 * Signature: int GetCockpitTimer(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCockpitTimer(lua_State *param_1)

{
  lua_pushinteger(param_1,cockpitTimer.timer);
  return 1;
}
