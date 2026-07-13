/*
 * Entry: 005cb524
 * Name: `dynamic_initializer_for_'recyclerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'recyclerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__recyclerClass__(void)

{
  RecyclerClass::RecyclerClass((RecyclerClass *)&recyclerClass);
  atexit(_dynamic_atexit_destructor_for__recyclerClass__);
  return;
}
