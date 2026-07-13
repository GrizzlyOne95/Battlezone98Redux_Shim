/*
 * Entry: 005cd033
 * Name: `dynamic_atexit_destructor_for_'proximityMineClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'proximityMineClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__proximityMineClass__(void)

{
  proximityMineClass._padding_ = (int)&ProximityMineClass::_vftable_;
  MineClass::~MineClass((MineClass *)&proximityMineClass);
  return;
}
