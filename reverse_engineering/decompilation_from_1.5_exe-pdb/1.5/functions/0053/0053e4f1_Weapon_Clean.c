/*
 * Entry: 0053e4f1
 * Name: Weapon_Clean
 * Namespace: Global
 * Signature: void Weapon_Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Weapon_Clean(void)

{
  Weapon **ppWVar1;
  
  while (Weapon::weaponList._Mysize != 0) {
    ppWVar1 = std::list<Weapon_*,std::allocator<Weapon_*>_>::back(&Weapon::weaponList);
    if (*ppWVar1 != (Weapon *)0x0) {
      (**(code **)(*ppWVar1)->_padding_)(1);
    }
  }
  return;
}
