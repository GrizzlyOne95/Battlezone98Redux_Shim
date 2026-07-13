/*
 * Entry: 005ccb8c
 * Name: `dynamic_atexit_destructor_for_'turretTankClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'turretTankClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__turretTankClass__(void)

{
  turretTankClass._padding_ = (int)&TurretTankClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&turretTankClass);
  return;
}
