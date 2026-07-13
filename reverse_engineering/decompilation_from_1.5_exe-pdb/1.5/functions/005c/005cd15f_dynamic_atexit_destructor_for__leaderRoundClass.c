/*
 * Entry: 005cd15f
 * Name: `dynamic_atexit_destructor_for_'leaderRoundClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'leaderRoundClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__leaderRoundClass__(void)

{
  leaderRoundClass._padding_ = (int)&TeamSwitcherClass::_vftable_;
  RocketClass::~RocketClass((RocketClass *)&leaderRoundClass);
  return;
}
