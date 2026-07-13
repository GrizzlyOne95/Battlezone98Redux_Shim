/*
 * Entry: 005cc3d5
 * Name: `dynamic_initializer_for_'specialItemClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'specialItemClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__specialItemClass__(void)

{
  SpecialItemClass::SpecialItemClass(&specialItemClass);
  atexit(_dynamic_atexit_destructor_for__specialItemClass__);
  return;
}
