/*
 * Entry: 005cd047
 * Name: `dynamic_atexit_destructor_for_'quakeBlastClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'quakeBlastClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__quakeBlastClass__(void)

{
  quakeBlastClass._padding_ = (int)&QuakeBlastClass::_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)&quakeBlastClass);
  return;
}
