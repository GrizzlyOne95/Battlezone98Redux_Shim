/*
 * Entry: 005ccf7d
 * Name: `dynamic_atexit_destructor_for_'objectLobberClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'objectLobberClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__objectLobberClass__(void)

{
  objectLobberClass._padding_ = (int)&ObjectLobberClass::_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)&objectLobberClass);
  return;
}
