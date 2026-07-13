/*
 * Entry: 005cc4dd
 * Name: `dynamic_initializer_for_'WeaponClass::classList''
 * Namespace: `dynamic_initializer_for_'WeaponClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'WeaponClass::classList__(void)

{
  std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::
  vector<WeaponClass_*,std::allocator<WeaponClass_*>_>(&WeaponClass::classList);
  atexit(`dynamic_atexit_destructor_for_'WeaponClass::classList__);
  return;
}
