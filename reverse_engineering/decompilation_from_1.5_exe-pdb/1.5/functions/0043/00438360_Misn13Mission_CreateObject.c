/*
 * Entry: 00438360
 * Name: Misn13Mission::CreateObject
 * Namespace: Misn13Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn13Mission::CreateObject(void)

{
  Misn13Mission *pMVar1;
  
  pMVar1 = operator_new(0x1f0);
  if (pMVar1 != (Misn13Mission *)0x0) {
    pMVar1 = Misn13Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
