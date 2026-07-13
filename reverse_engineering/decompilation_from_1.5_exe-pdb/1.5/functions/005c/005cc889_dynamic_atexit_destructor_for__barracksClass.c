/*
 * Entry: 005cc889
 * Name: `dynamic_atexit_destructor_for_'barracksClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'barracksClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__barracksClass__(void)

{
  barracksClass._padding_ = (int)&BarracksClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&barracksClass);
  return;
}
