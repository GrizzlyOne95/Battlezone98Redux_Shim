/*
 * Entry: 0042f21b
 * Name: Misn09Mission::CreateObject
 * Namespace: Misn09Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn09Mission::CreateObject(void)

{
  Misn09Mission *pMVar1;
  
  pMVar1 = operator_new(0x1e0);
  if (pMVar1 != (Misn09Mission *)0x0) {
    pMVar1 = Misn09Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
