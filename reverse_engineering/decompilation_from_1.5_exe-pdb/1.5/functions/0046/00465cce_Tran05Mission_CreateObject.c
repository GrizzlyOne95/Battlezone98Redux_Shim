/*
 * Entry: 00465cce
 * Name: Tran05Mission::CreateObject
 * Namespace: Tran05Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Tran05Mission::CreateObject(void)

{
  Tran05Mission *pTVar1;
  
  pTVar1 = operator_new(0xe8);
  if (pTVar1 != (Tran05Mission *)0x0) {
    pTVar1 = Tran05Mission(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
