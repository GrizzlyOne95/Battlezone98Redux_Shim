/*
 * Entry: 005ca867
 * Name: `dynamic_initializer_for_'armoryClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'armoryClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__armoryClass__(void)

{
  ArmoryClass::ArmoryClass((ArmoryClass *)&armoryClass);
  atexit(_dynamic_atexit_destructor_for__armoryClass__);
  return;
}
