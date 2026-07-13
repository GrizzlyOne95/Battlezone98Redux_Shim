/*
 * Entry: 005cc999
 * Name: `dynamic_atexit_destructor_for_'healthPowerupClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'healthPowerupClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__healthPowerupClass__(void)

{
  healthPowerupClass._padding_ = (int)&HealthPowerupClass::_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)&healthPowerupClass);
  return;
}
