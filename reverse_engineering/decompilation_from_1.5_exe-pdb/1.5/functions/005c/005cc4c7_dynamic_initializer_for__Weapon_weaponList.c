/*
 * Entry: 005cc4c7
 * Name: `dynamic_initializer_for_'Weapon::weaponList''
 * Namespace: `dynamic_initializer_for_'Weapon
 * Signature: void weaponList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Weapon::weaponList__(void)

{
  std::list<Weapon_*,std::allocator<Weapon_*>_>::list<Weapon_*,std::allocator<Weapon_*>_>
            (&Weapon::weaponList);
  atexit(`dynamic_atexit_destructor_for_'Weapon::weaponList__);
  return;
}
