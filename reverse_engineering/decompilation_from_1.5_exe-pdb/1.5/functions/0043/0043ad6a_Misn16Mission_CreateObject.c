/*
 * Entry: 0043ad6a
 * Name: Misn16Mission::CreateObject
 * Namespace: Misn16Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn16Mission::CreateObject(void)

{
  Misn16Mission *pMVar1;
  
  pMVar1 = operator_new(0xd4);
  if (pMVar1 != (Misn16Mission *)0x0) {
    pMVar1 = Misn16Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
