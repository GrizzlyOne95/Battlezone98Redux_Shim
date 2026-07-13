/*
 * Entry: 00415ac3
 * Name: Inst01Mission::CreateObject
 * Namespace: Inst01Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Inst01Mission::CreateObject(void)

{
  Inst01Mission *pIVar1;
  
  pIVar1 = operator_new(0x48);
  if (pIVar1 != (Inst01Mission *)0x0) {
    pIVar1 = Inst01Mission(pIVar1);
    return (SObject *)pIVar1;
  }
  return (SObject *)0x0;
}
