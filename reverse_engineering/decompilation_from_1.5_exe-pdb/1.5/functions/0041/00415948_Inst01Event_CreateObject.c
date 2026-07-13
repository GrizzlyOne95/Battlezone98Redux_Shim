/*
 * Entry: 00415948
 * Name: Inst01Event::CreateObject
 * Namespace: Inst01Event
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Inst01Event::CreateObject(void)

{
  Inst01Event *pIVar1;
  
  pIVar1 = operator_new(0x2c);
  if (pIVar1 != (Inst01Event *)0x0) {
    pIVar1 = Inst01Event(pIVar1);
    return (SObject *)pIVar1;
  }
  return (SObject *)0x0;
}
