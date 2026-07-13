/*
 * Entry: 005ccb78
 * Name: `dynamic_atexit_destructor_for_'turretCraftClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'turretCraftClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__turretCraftClass__(void)

{
  turretCraftClass._padding_ = (int)&TurretCraftClass::_vftable_;
  CraftClass::~CraftClass((CraftClass *)&turretCraftClass);
  return;
}
