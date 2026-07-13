/*
 * Entry: 005cc4f3
 * Name: `dynamic_initializer_for_'weaponClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'weaponClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__weaponClass__(void)

{
  WeaponClass::WeaponClass(&weaponClass);
  atexit(_dynamic_atexit_destructor_for__weaponClass__);
  return;
}
