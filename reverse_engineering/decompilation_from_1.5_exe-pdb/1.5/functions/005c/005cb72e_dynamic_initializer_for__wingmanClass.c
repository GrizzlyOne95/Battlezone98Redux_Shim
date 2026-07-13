/*
 * Entry: 005cb72e
 * Name: `dynamic_initializer_for_'wingmanClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'wingmanClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__wingmanClass__(void)

{
  WingmanClass::WingmanClass((WingmanClass *)&wingmanClass);
  atexit(_dynamic_atexit_destructor_for__wingmanClass__);
  return;
}
