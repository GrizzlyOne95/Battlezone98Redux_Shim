/*
 * Entry: 005ccd83
 * Name: `dynamic_atexit_destructor_for_'anchorRocketClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'anchorRocketClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__anchorRocketClass__(void)

{
  anchorRocketClass._padding_ = (int)&AnchorRocketClass::_vftable_;
  RocketClass::~RocketClass((RocketClass *)&anchorRocketClass);
  return;
}
