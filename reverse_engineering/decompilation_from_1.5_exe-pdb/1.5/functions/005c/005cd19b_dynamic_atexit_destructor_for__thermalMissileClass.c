/*
 * Entry: 005cd19b
 * Name: `dynamic_atexit_destructor_for_'thermalMissileClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'thermalMissileClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__thermalMissileClass__(void)

{
  thermalMissileClass._padding_ = (int)&ThermalMissileClass::_vftable_;
  MissileClass::~MissileClass((MissileClass *)&thermalMissileClass);
  return;
}
