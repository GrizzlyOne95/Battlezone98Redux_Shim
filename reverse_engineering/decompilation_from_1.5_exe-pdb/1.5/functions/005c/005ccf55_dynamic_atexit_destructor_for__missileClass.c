/*
 * Entry: 005ccf55
 * Name: `dynamic_atexit_destructor_for_'missileClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'missileClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__missileClass__(void)

{
  missileClass._padding_ = (int)&MissileClass::_vftable_;
  RocketClass::~RocketClass((RocketClass *)&missileClass);
  return;
}
