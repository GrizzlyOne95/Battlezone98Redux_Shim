/*
 * Entry: 005ccf19
 * Name: `dynamic_atexit_destructor_for_'machineGunClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'machineGunClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__machineGunClass__(void)

{
  machineGunClass._0_4_ = &MachineGunClass::_vftable_;
  CannonClass::~CannonClass((CannonClass *)&machineGunClass);
  return;
}
