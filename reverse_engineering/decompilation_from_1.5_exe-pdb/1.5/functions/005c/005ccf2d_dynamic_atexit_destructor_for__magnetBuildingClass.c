/*
 * Entry: 005ccf2d
 * Name: `dynamic_atexit_destructor_for_'magnetBuildingClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'magnetBuildingClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__magnetBuildingClass__(void)

{
  magnetBuildingClass._padding_ = (int)&MagnetMineClass::_vftable_;
  MineClass::~MineClass((MineClass *)&magnetBuildingClass);
  return;
}
