/*
 * Entry: 004a8ed2
 * Name: PowerUp_New
 * Namespace: Global
 * Signature: void * PowerUp_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl PowerUp_New(void)

{
  VEHICLE *pVVar1;
  
  pVVar1 = new_vehicle();
  pVVar1->subclass = (void *)0x0;
  return pVVar1;
}
