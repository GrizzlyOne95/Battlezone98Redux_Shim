/*
 * Entry: 0041863b
 * Name: StopCockpitTimer
 * Namespace: Global
 * Signature: int StopCockpitTimer(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopCockpitTimer(lua_State *param_1)

{
  cockpitTimer.active = false;
  return 0;
}
