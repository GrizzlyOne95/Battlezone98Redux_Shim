/*
 * Entry: 00442e56
 * Name: Misns2Mission::CreateObject
 * Namespace: Misns2Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns2Mission::CreateObject(void)

{
  Misns2Mission *pMVar1;
  
  pMVar1 = operator_new(0x25c);
  if (pMVar1 != (Misns2Mission *)0x0) {
    pMVar1 = Misns2Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
