/*
 * Entry: 004318cb
 * Name: Misn10Mission::CreateObject
 * Namespace: Misn10Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn10Mission::CreateObject(void)

{
  Misn10Mission *pMVar1;
  
  pMVar1 = operator_new(0x144);
  if (pMVar1 != (Misn10Mission *)0x0) {
    pMVar1 = Misn10Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
