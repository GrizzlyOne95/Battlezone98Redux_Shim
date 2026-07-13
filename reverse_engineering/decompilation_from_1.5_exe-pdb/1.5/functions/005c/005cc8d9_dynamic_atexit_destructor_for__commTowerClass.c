/*
 * Entry: 005cc8d9
 * Name: `dynamic_atexit_destructor_for_'commTowerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'commTowerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__commTowerClass__(void)

{
  commTowerClass._padding_ = (int)&CommTowerClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&commTowerClass);
  return;
}
