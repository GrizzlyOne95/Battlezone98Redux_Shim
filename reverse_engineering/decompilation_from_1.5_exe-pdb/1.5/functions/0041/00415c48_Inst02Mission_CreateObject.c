/*
 * Entry: 00415c48
 * Name: Inst02Mission::CreateObject
 * Namespace: Inst02Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Inst02Mission::CreateObject(void)

{
  Inst02Mission *pIVar1;
  
  pIVar1 = operator_new(0x48);
  if (pIVar1 != (Inst02Mission *)0x0) {
    pIVar1 = Inst02Mission(pIVar1);
    return (SObject *)pIVar1;
  }
  return (SObject *)0x0;
}
