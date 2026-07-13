/*
 * Entry: 005cd0d3
 * Name: `dynamic_atexit_destructor_for_'sniperGunClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'sniperGunClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__sniperGunClass__(void)

{
  sniperGunClass._0_4_ = &SniperGunClass::_vftable_;
  CannonClass::~CannonClass((CannonClass *)&sniperGunClass);
  return;
}
