/*
 * Entry: 005cd1af
 * Name: `dynamic_atexit_destructor_for_'torpedoClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'torpedoClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__torpedoClass__(void)

{
  torpedoClass._padding_ = (int)&TorpedoClass::_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)&torpedoClass);
  return;
}
