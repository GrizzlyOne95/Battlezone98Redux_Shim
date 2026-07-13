/*
 * Entry: 005ccb64
 * Name: `dynamic_atexit_destructor_for_'tugClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'tugClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__tugClass__(void)

{
  tugClass._padding_ = (int)&TugClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&tugClass);
  return;
}
