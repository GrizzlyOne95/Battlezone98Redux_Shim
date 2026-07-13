/*
 * Entry: 005cca32
 * Name: `dynamic_atexit_destructor_for_'powerUpClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'powerUpClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__powerUpClass__(void)

{
  powerUpClass._padding_ = (int)&PowerUpClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&powerUpClass);
  return;
}
