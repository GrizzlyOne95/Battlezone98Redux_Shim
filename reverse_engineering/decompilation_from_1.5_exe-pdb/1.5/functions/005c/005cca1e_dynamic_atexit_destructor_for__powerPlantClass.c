/*
 * Entry: 005cca1e
 * Name: `dynamic_atexit_destructor_for_'powerPlantClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'powerPlantClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__powerPlantClass__(void)

{
  powerPlantClass._padding_ = (int)&PowerPlantClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&powerPlantClass);
  return;
}
