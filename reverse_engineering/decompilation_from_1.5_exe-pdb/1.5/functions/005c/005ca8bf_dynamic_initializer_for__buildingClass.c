/*
 * Entry: 005ca8bf
 * Name: `dynamic_initializer_for_'buildingClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'buildingClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__buildingClass__(void)

{
  BuildingClass::BuildingClass(&buildingClass);
  atexit(_dynamic_atexit_destructor_for__buildingClass__);
  return;
}
