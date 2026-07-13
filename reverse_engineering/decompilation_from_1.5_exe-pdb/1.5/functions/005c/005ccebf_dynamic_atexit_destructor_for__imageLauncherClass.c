/*
 * Entry: 005ccebf
 * Name: `dynamic_atexit_destructor_for_'imageLauncherClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'imageLauncherClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__imageLauncherClass__(void)

{
  imageLauncherClass._0_4_ = &ImageLauncherClass::_vftable_;
  LauncherClass::~LauncherClass((LauncherClass *)&imageLauncherClass);
  return;
}
