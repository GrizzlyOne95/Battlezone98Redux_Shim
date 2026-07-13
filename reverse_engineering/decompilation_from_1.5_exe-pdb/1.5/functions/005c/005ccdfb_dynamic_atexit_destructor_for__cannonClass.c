/*
 * Entry: 005ccdfb
 * Name: `dynamic_atexit_destructor_for_'cannonClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'cannonClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__cannonClass__(void)

{
  cannonClass._padding_ = (int)&CannonClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&cannonClass);
  return;
}
