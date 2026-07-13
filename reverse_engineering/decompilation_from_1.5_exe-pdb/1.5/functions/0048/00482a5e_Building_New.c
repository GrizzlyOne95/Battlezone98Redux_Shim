/*
 * Entry: 00482a5e
 * Name: Building_New
 * Namespace: Global
 * Signature: void * Building_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Building_New(void)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(8);
  *puVar1 = 0;
  puVar1[1] = 0;
  terrainChanged = 1;
  return puVar1;
}
