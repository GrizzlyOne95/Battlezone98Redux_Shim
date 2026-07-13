/*
 * Entry: 005cc443
 * Name: `dynamic_initializer_for_'leaderRoundClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'leaderRoundClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__leaderRoundClass__(void)

{
  TeamSwitcherClass::TeamSwitcherClass(&leaderRoundClass);
  atexit(_dynamic_atexit_destructor_for__leaderRoundClass__);
  return;
}
