/*
 * Entry: 005cd00b
 * Name: `dynamic_atexit_destructor_for_'popperClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'popperClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__popperClass__(void)

{
  popperClass._padding_ = (int)&PopperClass::_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)&popperClass);
  return;
}
