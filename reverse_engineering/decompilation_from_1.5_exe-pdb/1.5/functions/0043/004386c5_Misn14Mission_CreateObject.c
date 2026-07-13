/*
 * Entry: 004386c5
 * Name: Misn14Mission::CreateObject
 * Namespace: Misn14Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn14Mission::CreateObject(void)

{
  Misn14Mission *pMVar1;
  
  pMVar1 = operator_new(0xec);
  if (pMVar1 != (Misn14Mission *)0x0) {
    pMVar1 = Misn14Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
