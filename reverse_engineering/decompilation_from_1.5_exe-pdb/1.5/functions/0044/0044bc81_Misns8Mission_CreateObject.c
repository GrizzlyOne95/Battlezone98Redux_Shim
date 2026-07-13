/*
 * Entry: 0044bc81
 * Name: Misns8Mission::CreateObject
 * Namespace: Misns8Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns8Mission::CreateObject(void)

{
  Misns8Mission *pMVar1;
  
  pMVar1 = operator_new(0x2ac);
  if (pMVar1 != (Misns8Mission *)0x0) {
    pMVar1 = Misns8Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
