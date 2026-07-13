/*
 * Entry: 005ccd97
 * Name: `dynamic_atexit_destructor_for_'beamClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'beamClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__beamClass__(void)

{
  beamClass._padding_ = (int)&BeamClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&beamClass);
  return;
}
