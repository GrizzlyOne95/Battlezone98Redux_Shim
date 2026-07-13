/*
 * Entry: 005cc798
 * Name: `dynamic_atexit_destructor_for_'animBuildingClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'animBuildingClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__animBuildingClass__(void)

{
  animBuildingClass._0_4_ = &AnimBuildingClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&animBuildingClass);
  return;
}
