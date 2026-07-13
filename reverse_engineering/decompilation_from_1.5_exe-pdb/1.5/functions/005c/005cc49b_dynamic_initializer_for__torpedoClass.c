/*
 * Entry: 005cc49b
 * Name: `dynamic_initializer_for_'torpedoClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'torpedoClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__torpedoClass__(void)

{
  TorpedoClass::TorpedoClass((TorpedoClass *)&torpedoClass);
  atexit(_dynamic_atexit_destructor_for__torpedoClass__);
  return;
}
