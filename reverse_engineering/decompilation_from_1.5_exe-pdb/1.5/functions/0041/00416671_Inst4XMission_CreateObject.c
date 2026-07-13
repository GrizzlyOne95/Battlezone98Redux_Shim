/*
 * Entry: 00416671
 * Name: Inst4XMission::CreateObject
 * Namespace: Inst4XMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Inst4XMission::CreateObject(void)

{
  Inst4XMission *pIVar1;
  
  pIVar1 = operator_new(0x6c);
  if (pIVar1 != (Inst4XMission *)0x0) {
    pIVar1 = Inst4XMission(pIVar1);
    return (SObject *)pIVar1;
  }
  return (SObject *)0x0;
}
