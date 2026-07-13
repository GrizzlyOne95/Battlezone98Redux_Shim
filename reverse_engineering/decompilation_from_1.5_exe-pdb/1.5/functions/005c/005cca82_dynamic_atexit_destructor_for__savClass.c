/*
 * Entry: 005cca82
 * Name: `dynamic_atexit_destructor_for_'savClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'savClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__savClass__(void)

{
  savClass._padding_ = (int)&SAVClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&savClass);
  return;
}
