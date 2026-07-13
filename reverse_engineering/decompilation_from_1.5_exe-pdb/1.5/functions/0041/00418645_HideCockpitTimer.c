/*
 * Entry: 00418645
 * Name: HideCockpitTimer
 * Namespace: Global
 * Signature: int HideCockpitTimer(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HideCockpitTimer(lua_State *param_1)

{
  CockpitTimer::HideTimer(&cockpitTimer);
  return 0;
}
