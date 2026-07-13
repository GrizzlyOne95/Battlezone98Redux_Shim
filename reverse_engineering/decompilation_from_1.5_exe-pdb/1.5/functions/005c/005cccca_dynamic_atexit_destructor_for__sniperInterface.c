/*
 * Entry: 005cccca
 * Name: `dynamic_atexit_destructor_for_'sniperInterface''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'sniperInterface''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__sniperInterface__(void)

{
  sniperInterface._padding_ = (int)&SniperInterface::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&sniperInterface);
  return;
}
