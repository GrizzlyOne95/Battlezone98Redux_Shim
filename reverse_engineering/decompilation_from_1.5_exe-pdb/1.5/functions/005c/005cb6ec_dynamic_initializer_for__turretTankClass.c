/*
 * Entry: 005cb6ec
 * Name: `dynamic_initializer_for_'turretTankClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'turretTankClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__turretTankClass__(void)

{
  TurretTankClass::TurretTankClass((TurretTankClass *)&turretTankClass);
  atexit(_dynamic_atexit_destructor_for__turretTankClass__);
  return;
}
