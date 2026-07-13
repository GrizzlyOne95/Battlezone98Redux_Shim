/*
 * Entry: 005cc9d5
 * Name: `dynamic_atexit_destructor_for_'minelayerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'minelayerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__minelayerClass__(void)

{
  minelayerClass._padding_ = (int)&MinelayerClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&minelayerClass);
  return;
}
