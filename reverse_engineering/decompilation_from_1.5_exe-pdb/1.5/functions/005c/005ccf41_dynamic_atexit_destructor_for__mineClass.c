/*
 * Entry: 005ccf41
 * Name: `dynamic_atexit_destructor_for_'mineClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'mineClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__mineClass__(void)

{
  mineClass._padding_ = (int)&MineClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&mineClass);
  return;
}
