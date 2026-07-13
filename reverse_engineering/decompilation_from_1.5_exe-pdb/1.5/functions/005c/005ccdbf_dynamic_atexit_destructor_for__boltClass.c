/*
 * Entry: 005ccdbf
 * Name: `dynamic_atexit_destructor_for_'boltClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'boltClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__boltClass__(void)

{
  boltClass._padding_ = (int)&BoltClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&boltClass);
  return;
}
