/*
 * Entry: 005ca851
 * Name: `dynamic_initializer_for_'apcClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'apcClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__apcClass__(void)

{
  APCClass::APCClass((APCClass *)&apcClass);
  atexit(_dynamic_atexit_destructor_for__apcClass__);
  return;
}
