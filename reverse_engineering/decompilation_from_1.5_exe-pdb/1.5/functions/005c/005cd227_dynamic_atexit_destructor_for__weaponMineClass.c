/*
 * Entry: 005cd227
 * Name: `dynamic_atexit_destructor_for_'weaponMineClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'weaponMineClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__weaponMineClass__(void)

{
  weaponMineClass._padding_ = (int)&WeaponMineClass::_vftable_;
  MineClass::~MineClass((MineClass *)&weaponMineClass);
  return;
}
