/*
 * Entry: 005cb83c
 * Name: `dynamic_initializer_for_'cockpitTimer''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'cockpitTimer''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__cockpitTimer__(void)

{
  CockpitTimer::CockpitTimer(&cockpitTimer);
  atexit(_dynamic_atexit_destructor_for__cockpitTimer__);
  return;
}
