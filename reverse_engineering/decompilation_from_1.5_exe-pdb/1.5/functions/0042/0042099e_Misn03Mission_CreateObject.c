/*
 * Entry: 0042099e
 * Name: Misn03Mission::CreateObject
 * Namespace: Misn03Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn03Mission::CreateObject(void)

{
  Misn03Mission *pMVar1;
  
  pMVar1 = operator_new(0x250);
  if (pMVar1 != (Misn03Mission *)0x0) {
    pMVar1 = Misn03Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
