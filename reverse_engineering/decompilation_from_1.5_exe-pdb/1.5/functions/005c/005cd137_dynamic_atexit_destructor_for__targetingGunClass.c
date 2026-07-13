/*
 * Entry: 005cd137
 * Name: `dynamic_atexit_destructor_for_'targetingGunClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'targetingGunClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__targetingGunClass__(void)

{
  targetingGunClass._padding_ = (int)&TargetingGunClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&targetingGunClass);
  return;
}
