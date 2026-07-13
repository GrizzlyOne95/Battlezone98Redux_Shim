/*
 * Entry: 005cd210
 * Name: `dynamic_atexit_destructor_for_'WeaponClass::classList''
 * Namespace: `dynamic_atexit_destructor_for_'WeaponClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'WeaponClass::classList__(void)

{
  std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Tidy(&WeaponClass::classList);
  operator_delete((void *)WeaponClass::classList._padding_);
  return;
}
