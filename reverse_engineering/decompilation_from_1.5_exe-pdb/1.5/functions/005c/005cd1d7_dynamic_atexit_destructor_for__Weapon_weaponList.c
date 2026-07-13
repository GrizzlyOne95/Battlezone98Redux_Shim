/*
 * Entry: 005cd1d7
 * Name: `dynamic_atexit_destructor_for_'Weapon::weaponList''
 * Namespace: `dynamic_atexit_destructor_for_'Weapon
 * Signature: void weaponList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Weapon::weaponList__(void)

{
  std::list<Weapon_*,std::allocator<Weapon_*>_>::_Tidy(&Weapon::weaponList);
  operator_delete((void *)Weapon::weaponList._padding_);
  return;
}
