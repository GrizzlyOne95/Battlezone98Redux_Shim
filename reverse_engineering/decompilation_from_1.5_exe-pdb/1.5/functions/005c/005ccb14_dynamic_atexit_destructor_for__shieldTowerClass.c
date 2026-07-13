/*
 * Entry: 005ccb14
 * Name: `dynamic_atexit_destructor_for_'shieldTowerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'shieldTowerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__shieldTowerClass__(void)

{
  shieldTowerClass._padding_ = (int)&ShieldTowerClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&shieldTowerClass);
  return;
}
