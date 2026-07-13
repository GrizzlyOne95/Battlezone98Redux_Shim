/*
 * Entry: 005cd097
 * Name: `dynamic_atexit_destructor_for_'rocketClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'rocketClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__rocketClass__(void)

{
  rocketClass._padding_ = (int)&RocketClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&rocketClass);
  return;
}
