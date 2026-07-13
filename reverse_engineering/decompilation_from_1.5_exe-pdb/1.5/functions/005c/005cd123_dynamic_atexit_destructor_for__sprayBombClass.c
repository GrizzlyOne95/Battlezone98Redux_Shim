/*
 * Entry: 005cd123
 * Name: `dynamic_atexit_destructor_for_'sprayBombClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'sprayBombClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__sprayBombClass__(void)

{
  sprayBombClass._padding_ = (int)&SprayBombClass::_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)&sprayBombClass);
  return;
}
