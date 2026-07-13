/*
 * Entry: 005ccdd3
 * Name: `dynamic_atexit_destructor_for_'bounceBombClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'bounceBombClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__bounceBombClass__(void)

{
  bounceBombClass._padding_ = (int)&BounceBombClass::_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)&bounceBombClass);
  return;
}
