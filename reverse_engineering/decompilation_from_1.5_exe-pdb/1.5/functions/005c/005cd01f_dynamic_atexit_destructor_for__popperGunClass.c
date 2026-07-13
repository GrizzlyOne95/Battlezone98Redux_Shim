/*
 * Entry: 005cd01f
 * Name: `dynamic_atexit_destructor_for_'popperGunClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'popperGunClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__popperGunClass__(void)

{
  popperGunClass._padding_ = (int)&PopperGunClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&popperGunClass);
  return;
}
