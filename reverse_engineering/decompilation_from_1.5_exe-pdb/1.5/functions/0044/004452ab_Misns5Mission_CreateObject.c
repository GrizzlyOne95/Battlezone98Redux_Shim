/*
 * Entry: 004452ab
 * Name: Misns5Mission::CreateObject
 * Namespace: Misns5Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns5Mission::CreateObject(void)

{
  Misns5Mission *pMVar1;
  
  pMVar1 = operator_new(0xb8);
  if (pMVar1 != (Misns5Mission *)0x0) {
    pMVar1 = Misns5Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
