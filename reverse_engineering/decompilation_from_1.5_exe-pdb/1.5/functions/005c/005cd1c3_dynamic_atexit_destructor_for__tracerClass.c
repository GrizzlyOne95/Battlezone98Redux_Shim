/*
 * Entry: 005cd1c3
 * Name: `dynamic_atexit_destructor_for_'tracerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'tracerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__tracerClass__(void)

{
  tracerClass._padding_ = (int)&TracerClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&tracerClass);
  return;
}
