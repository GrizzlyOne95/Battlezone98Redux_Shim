/*
 * Entry: 005cce83
 * Name: `dynamic_atexit_destructor_for_'flareBuildingClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'flareBuildingClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__flareBuildingClass__(void)

{
  flareBuildingClass._padding_ = (int)&FlareMineClass::_vftable_;
  MineClass::~MineClass((MineClass *)&flareBuildingClass);
  return;
}
