/*
 * Entry: 005cd0fb
 * Name: `dynamic_atexit_destructor_for_'specialItemClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'specialItemClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__specialItemClass__(void)

{
  specialItemClass._padding_ = (int)&SpecialItemClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&specialItemClass);
  return;
}
