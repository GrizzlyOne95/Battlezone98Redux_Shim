/*
 * Entry: 0046438a
 * Name: Tran02Mission::CreateObject
 * Namespace: Tran02Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Tran02Mission::CreateObject(void)

{
  Tran02Mission *pTVar1;
  
  pTVar1 = operator_new(0x9c);
  if (pTVar1 != (Tran02Mission *)0x0) {
    pTVar1 = Tran02Mission(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
