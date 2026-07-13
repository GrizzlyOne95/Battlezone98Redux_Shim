/*
 * Entry: 005cce23
 * Name: `dynamic_atexit_destructor_for_'dispenserClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'dispenserClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__dispenserClass__(void)

{
  dispenserClass._padding_ = (int)&DispenserClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&dispenserClass);
  return;
}
