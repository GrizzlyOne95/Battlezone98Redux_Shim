/*
 * Entry: 0043a264
 * Name: Misn15Mission::CreateObject
 * Namespace: Misn15Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn15Mission::CreateObject(void)

{
  Misn15Mission *pMVar1;
  
  pMVar1 = operator_new(0x294);
  if (pMVar1 != (Misn15Mission *)0x0) {
    pMVar1 = Misn15Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
