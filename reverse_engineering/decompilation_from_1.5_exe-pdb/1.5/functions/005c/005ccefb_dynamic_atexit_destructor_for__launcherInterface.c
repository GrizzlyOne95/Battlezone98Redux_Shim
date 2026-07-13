/*
 * Entry: 005ccefb
 * Name: `dynamic_atexit_destructor_for_'launcherInterface''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'launcherInterface''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__launcherInterface__(void)

{
  launcherInterface._padding_ = (int)&LauncherInterface::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&launcherInterface);
  return;
}
