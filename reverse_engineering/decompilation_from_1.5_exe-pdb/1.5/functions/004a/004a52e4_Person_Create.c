/*
 * Entry: 004a52e4
 * Name: Person_Create
 * Namespace: Global
 * Signature: VEHICLE * Person_Create(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VEHICLE * __cdecl Person_Create(void)

{
  VEHICLE *pVVar1;
  
  pVVar1 = new_vehicle();
  pVVar1->subclass = (void *)0x0;
  return pVVar1;
}
