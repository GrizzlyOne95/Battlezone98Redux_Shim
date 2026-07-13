/*
 * Entry: 00448993
 * Name: Misns7Mission::CreateObject
 * Namespace: Misns7Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns7Mission::CreateObject(void)

{
  Misns7Mission *pMVar1;
  
  pMVar1 = operator_new(0x278);
  if (pMVar1 != (Misns7Mission *)0x0) {
    pMVar1 = Misns7Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
