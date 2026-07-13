/*
 * Entry: 005cc9ad
 * Name: `dynamic_atexit_destructor_for_'hoverCraftClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'hoverCraftClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__hoverCraftClass__(void)

{
  hoverCraftClass._padding_ = (int)&HoverCraftClass::_vftable_;
  CraftClass::~CraftClass((CraftClass *)&hoverCraftClass);
  return;
}
