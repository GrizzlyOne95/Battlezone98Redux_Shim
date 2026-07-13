/*
 * Entry: 005ca8a9
 * Name: `dynamic_initializer_for_'barracksClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'barracksClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__barracksClass__(void)

{
  BarracksClass::BarracksClass(&barracksClass);
  atexit(_dynamic_atexit_destructor_for__barracksClass__);
  return;
}
