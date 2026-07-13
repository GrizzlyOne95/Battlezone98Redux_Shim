/*
 * Entry: 00429311
 * Name: Misn06Mission::CreateObject
 * Namespace: Misn06Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn06Mission::CreateObject(void)

{
  Misn06Mission *pMVar1;
  
  pMVar1 = operator_new(0x350);
  if (pMVar1 != (Misn06Mission *)0x0) {
    pMVar1 = Misn06Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
