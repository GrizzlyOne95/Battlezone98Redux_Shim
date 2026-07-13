/*
 * Entry: 00440408
 * Name: Misns1Mission::CreateObject
 * Namespace: Misns1Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns1Mission::CreateObject(void)

{
  Misns1Mission *pMVar1;
  
  pMVar1 = operator_new(0x1cc);
  if (pMVar1 != (Misns1Mission *)0x0) {
    pMVar1 = Misns1Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
