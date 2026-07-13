/*
 * Entry: 0041d824
 * Name: Misn01Mission::CreateObject
 * Namespace: Misn01Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misn01Mission::CreateObject(void)

{
  Misn01Mission *pMVar1;
  
  pMVar1 = operator_new(0x98);
  if (pMVar1 != (Misn01Mission *)0x0) {
    pMVar1 = Misn01Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
