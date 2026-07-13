/*
 * Entry: 005cc836
 * Name: `dynamic_atexit_destructor_for_'apcClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'apcClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__apcClass__(void)

{
  apcClass._padding_ = (int)&APCClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&apcClass);
  return;
}
