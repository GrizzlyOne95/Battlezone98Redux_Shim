/*
 * Entry: 005cc784
 * Name: `dynamic_atexit_destructor_for_'ammoPowerupClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'ammoPowerupClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__ammoPowerupClass__(void)

{
  ammoPowerupClass._padding_ = (int)&AmmoPowerupClass::_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)&ammoPowerupClass);
  return;
}
