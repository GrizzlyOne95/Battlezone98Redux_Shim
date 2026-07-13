/*
 * Entry: 005cce97
 * Name: `dynamic_atexit_destructor_for_'grenadeClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'grenadeClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__grenadeClass__(void)

{
  grenadeClass._0_4_ = &GrenadeClass::_vftable_;
  RocketClass::~RocketClass((RocketClass *)&grenadeClass);
  return;
}
