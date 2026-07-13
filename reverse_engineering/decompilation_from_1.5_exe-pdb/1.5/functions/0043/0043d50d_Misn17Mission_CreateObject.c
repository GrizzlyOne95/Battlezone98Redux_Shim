/*
 * Entry: 0043d50d
 * Name: Misn17Mission::CreateObject
 * Namespace: Misn17Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn17Mission::CreateObject(void)

{
  Misn17Mission *pMVar1;
  
  pMVar1 = operator_new(0x35c);
  if (pMVar1 != (Misn17Mission *)0x0) {
    pMVar1 = Misn17Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
