/*
 * Entry: 005cd10f
 * Name: `dynamic_atexit_destructor_for_'sprayBuildingClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'sprayBuildingClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__sprayBuildingClass__(void)

{
  sprayBuildingClass._padding_ = (int)&SprayBuildingClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&sprayBuildingClass);
  return;
}
