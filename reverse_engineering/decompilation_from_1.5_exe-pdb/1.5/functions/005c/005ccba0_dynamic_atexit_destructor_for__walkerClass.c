/*
 * Entry: 005ccba0
 * Name: `dynamic_atexit_destructor_for_'walkerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'walkerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__walkerClass__(void)

{
  walkerClass._padding_ = (int)&WalkerClass::_vftable_;
  CraftClass::~CraftClass((CraftClass *)&walkerClass);
  return;
}
