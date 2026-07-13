/*
 * Entry: 005cd0e7
 * Name: `dynamic_atexit_destructor_for_'sniperShellClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'sniperShellClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__sniperShellClass__(void)

{
  sniperShellClass._padding_ = (int)&SniperShellClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&sniperShellClass);
  return;
}
