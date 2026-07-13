/*
 * Entry: 0042d770
 * Name: Misn08Mission::CreateObject
 * Namespace: Misn08Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn08Mission::CreateObject(void)

{
  Misn08Mission *pMVar1;
  
  pMVar1 = operator_new(0x1ac);
  if (pMVar1 != (Misn08Mission *)0x0) {
    pMVar1 = Misn08Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
