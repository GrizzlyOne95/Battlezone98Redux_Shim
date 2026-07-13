/*
 * Entry: 005ccbb4
 * Name: `dynamic_atexit_destructor_for_'weaponPowerupClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'weaponPowerupClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__weaponPowerupClass__(void)

{
  weaponPowerupClass._padding_ = (int)&WeaponPowerupClass::_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)&weaponPowerupClass);
  return;
}
