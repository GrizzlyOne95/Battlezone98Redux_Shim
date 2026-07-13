/*
 * Entry: 00426441
 * Name: Misn05Mission::CreateObject
 * Namespace: Misn05Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn05Mission::CreateObject(void)

{
  Misn05Mission *pMVar1;
  
  pMVar1 = operator_new(0x23c);
  if (pMVar1 != (Misn05Mission *)0x0) {
    pMVar1 = Misn05Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
