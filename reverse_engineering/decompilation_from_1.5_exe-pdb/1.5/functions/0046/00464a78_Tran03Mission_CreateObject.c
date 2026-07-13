/*
 * Entry: 00464a78
 * Name: Tran03Mission::CreateObject
 * Namespace: Tran03Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Tran03Mission::CreateObject(void)

{
  Tran03Mission *pTVar1;
  
  pTVar1 = operator_new(0x94);
  if (pTVar1 != (Tran03Mission *)0x0) {
    pTVar1 = Tran03Mission(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
