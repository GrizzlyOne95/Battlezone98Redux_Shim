/*
 * Entry: 005cc509
 * Name: `dynamic_initializer_for_'weaponMineClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'weaponMineClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__weaponMineClass__(void)

{
  WeaponMineClass::WeaponMineClass(&weaponMineClass);
  atexit(_dynamic_atexit_destructor_for__weaponMineClass__);
  return;
}
