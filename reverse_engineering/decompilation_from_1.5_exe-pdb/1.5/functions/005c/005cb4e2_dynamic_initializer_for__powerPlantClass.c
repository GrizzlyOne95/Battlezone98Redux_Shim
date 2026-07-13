/*
 * Entry: 005cb4e2
 * Name: `dynamic_initializer_for_'powerPlantClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'powerPlantClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__powerPlantClass__(void)

{
  PowerPlantClass::PowerPlantClass(&powerPlantClass);
  atexit(_dynamic_atexit_destructor_for__powerPlantClass__);
  return;
}
