/*
 * Entry: 005cb87b
 * Name: `dynamic_initializer_for_'controlPanel''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'controlPanel''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__controlPanel__(void)

{
  ControlPanel::ControlPanel(&controlPanel);
  atexit(_dynamic_atexit_destructor_for__controlPanel__);
  return;
}
