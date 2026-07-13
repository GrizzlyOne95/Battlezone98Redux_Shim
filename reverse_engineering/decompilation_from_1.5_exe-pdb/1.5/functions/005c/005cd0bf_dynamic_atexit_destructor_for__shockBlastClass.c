/*
 * Entry: 005cd0bf
 * Name: `dynamic_atexit_destructor_for_'shockBlastClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'shockBlastClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__shockBlastClass__(void)

{
  shockBlastClass._0_4_ = &ShockBlastClass::_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)&shockBlastClass);
  return;
}
