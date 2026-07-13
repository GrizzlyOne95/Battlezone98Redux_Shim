/*
 * Entry: 00415d56
 * Name: Inst03Mission::CreateObject
 * Namespace: Inst03Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Inst03Mission::CreateObject(void)

{
  Inst03Mission *pIVar1;
  
  pIVar1 = operator_new(0x4c);
  if (pIVar1 != (Inst03Mission *)0x0) {
    pIVar1 = Inst03Mission(pIVar1);
    return (SObject *)pIVar1;
  }
  return (SObject *)0x0;
}
