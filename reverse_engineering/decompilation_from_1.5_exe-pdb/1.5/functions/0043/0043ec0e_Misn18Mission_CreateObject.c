/*
 * Entry: 0043ec0e
 * Name: Misn18Mission::CreateObject
 * Namespace: Misn18Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn18Mission::CreateObject(void)

{
  Misn18Mission *pMVar1;
  
  pMVar1 = operator_new(0x1c0);
  if (pMVar1 != (Misn18Mission *)0x0) {
    pMVar1 = Misn18Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
