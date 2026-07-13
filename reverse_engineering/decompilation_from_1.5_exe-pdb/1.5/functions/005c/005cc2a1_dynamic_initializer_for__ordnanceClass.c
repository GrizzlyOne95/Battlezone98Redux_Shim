/*
 * Entry: 005cc2a1
 * Name: `dynamic_initializer_for_'ordnanceClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'ordnanceClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__ordnanceClass__(void)

{
  OrdnanceClass::OrdnanceClass(&ordnanceClass);
  atexit(_dynamic_atexit_destructor_for__ordnanceClass__);
  return;
}
