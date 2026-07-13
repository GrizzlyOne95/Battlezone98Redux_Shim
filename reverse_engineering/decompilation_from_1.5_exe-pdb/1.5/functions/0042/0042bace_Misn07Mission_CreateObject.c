/*
 * Entry: 0042bace
 * Name: Misn07Mission::CreateObject
 * Namespace: Misn07Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn07Mission::CreateObject(void)

{
  Misn07Mission *pMVar1;
  
  pMVar1 = operator_new(0x6e4);
  if (pMVar1 != (Misn07Mission *)0x0) {
    pMVar1 = Misn07Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
