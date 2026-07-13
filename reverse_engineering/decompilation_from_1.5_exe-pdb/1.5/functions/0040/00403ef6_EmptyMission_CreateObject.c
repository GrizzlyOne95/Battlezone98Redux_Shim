/*
 * Entry: 00403ef6
 * Name: EmptyMission::CreateObject
 * Namespace: EmptyMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl EmptyMission::CreateObject(void)

{
  EmptyMission *pEVar1;
  
  pEVar1 = operator_new(0x40);
  if (pEVar1 != (EmptyMission *)0x0) {
    pEVar1 = EmptyMission(pEVar1);
    return (SObject *)pEVar1;
  }
  return (SObject *)0x0;
}
