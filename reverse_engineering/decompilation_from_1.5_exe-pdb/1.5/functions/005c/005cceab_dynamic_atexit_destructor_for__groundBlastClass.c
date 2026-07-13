/*
 * Entry: 005cceab
 * Name: `dynamic_atexit_destructor_for_'groundBlastClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'groundBlastClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__groundBlastClass__(void)

{
  groundBlastClass._0_4_ = &GroundBlastClass::_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)&groundBlastClass);
  return;
}
