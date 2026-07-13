/*
 * Entry: 005cb57c
 * Name: `dynamic_initializer_for_'scavengerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'scavengerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__scavengerClass__(void)

{
  ScavengerClass::ScavengerClass((ScavengerClass *)&scavengerClass);
  atexit(_dynamic_atexit_destructor_for__scavengerClass__);
  return;
}
