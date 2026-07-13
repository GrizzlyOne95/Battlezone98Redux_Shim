/*
 * Entry: 005ccff7
 * Name: `dynamic_atexit_destructor_for_'planarExplosionClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'planarExplosionClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__planarExplosionClass__(void)

{
  planarExplosionClass._0_4_ = &PlanarExplosionClass::_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)&planarExplosionClass);
  return;
}
