/*
 * Entry: 00436212
 * Name: Misn12Mission::CreateObject
 * Namespace: Misn12Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn12Mission::CreateObject(void)

{
  Misn12Mission *pMVar1;
  
  pMVar1 = operator_new(0x200);
  if (pMVar1 != (Misn12Mission *)0x0) {
    pMVar1 = Misn12Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
