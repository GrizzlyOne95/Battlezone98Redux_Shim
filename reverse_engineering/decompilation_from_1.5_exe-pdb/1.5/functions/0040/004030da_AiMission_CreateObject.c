/*
 * Entry: 004030da
 * Name: AiMission::CreateObject
 * Namespace: AiMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl AiMission::CreateObject(void)

{
  AiMission *pAVar1;
  
  pAVar1 = operator_new(0x40);
  if (pAVar1 != (AiMission *)0x0) {
    pAVar1 = AiMission(pAVar1);
    return (SObject *)pAVar1;
  }
  return (SObject *)0x0;
}
