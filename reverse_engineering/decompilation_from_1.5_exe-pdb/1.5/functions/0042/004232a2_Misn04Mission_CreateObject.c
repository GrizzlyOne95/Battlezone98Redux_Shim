/*
 * Entry: 004232a2
 * Name: Misn04Mission::CreateObject
 * Namespace: Misn04Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn04Mission::CreateObject(void)

{
  Misn04Mission *pMVar1;
  
  pMVar1 = operator_new(0x224);
  if (pMVar1 != (Misn04Mission *)0x0) {
    pMVar1 = Misn04Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
