/*
 * Entry: 005cb550
 * Name: `dynamic_initializer_for_'savClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'savClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__savClass__(void)

{
  SAVClass::SAVClass((SAVClass *)&savClass);
  atexit(_dynamic_atexit_destructor_for__savClass__);
  return;
}
