/*
 * Entry: 005ccdab
 * Name: `dynamic_atexit_destructor_for_'beamGunClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'beamGunClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__beamGunClass__(void)

{
  beamGunClass._0_4_ = &BeamGunClass::_vftable_;
  CannonClass::~CannonClass((CannonClass *)&beamGunClass);
  return;
}
