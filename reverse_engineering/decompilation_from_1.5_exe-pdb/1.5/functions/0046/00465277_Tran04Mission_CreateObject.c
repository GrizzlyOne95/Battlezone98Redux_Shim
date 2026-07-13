/*
 * Entry: 00465277
 * Name: Tran04Mission::CreateObject
 * Namespace: Tran04Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Tran04Mission::CreateObject(void)

{
  Tran04Mission *pTVar1;
  
  pTVar1 = operator_new(0xb8);
  if (pTVar1 != (Tran04Mission *)0x0) {
    pTVar1 = Tran04Mission(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
