/*
 * Entry: 00431bef
 * Name: Misn11Mission::CreateObject
 * Namespace: Misn11Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn11Mission::CreateObject(void)

{
  Misn11Mission *pMVar1;
  
  pMVar1 = operator_new(0xb8);
  if (pMVar1 != (Misn11Mission *)0x0) {
    pMVar1 = Misn11Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
