/*
 * Entry: 005cd06f
 * Name: `dynamic_atexit_destructor_for_'radarLauncherClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'radarLauncherClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__radarLauncherClass__(void)

{
  radarLauncherClass._0_4_ = &RadarLauncherClass::_vftable_;
  LauncherClass::~LauncherClass((LauncherClass *)&radarLauncherClass);
  return;
}
