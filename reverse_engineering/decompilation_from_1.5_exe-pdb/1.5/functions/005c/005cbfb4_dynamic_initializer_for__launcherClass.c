/*
 * Entry: 005cbfb4
 * Name: `dynamic_initializer_for_'launcherClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'launcherClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__launcherClass__(void)

{
  LauncherClass::LauncherClass(&launcherClass);
  atexit(_dynamic_atexit_destructor_for__launcherClass__);
  return;
}
