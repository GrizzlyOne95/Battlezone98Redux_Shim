/*
 * Entry: 0044419c
 * Name: Misns3Mission::CreateObject
 * Namespace: Misns3Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns3Mission::CreateObject(void)

{
  Misns3Mission *pMVar1;
  
  pMVar1 = operator_new(0x124);
  if (pMVar1 != (Misns3Mission *)0x0) {
    pMVar1 = Misns3Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
