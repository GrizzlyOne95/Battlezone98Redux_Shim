/*
 * Entry: 005ccaad
 * Name: `dynamic_atexit_destructor_for_'scavengerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'scavengerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__scavengerClass__(void)

{
  scavengerClass._padding_ = (int)&ScavengerClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&scavengerClass);
  return;
}
