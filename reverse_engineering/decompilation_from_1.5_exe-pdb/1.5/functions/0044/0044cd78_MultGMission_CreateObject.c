/*
 * Entry: 0044cd78
 * Name: MultGMission::CreateObject
 * Namespace: MultGMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MultGMission::CreateObject(void)

{
  MultGMission *pMVar1;
  
  pMVar1 = operator_new(0x40);
  if (pMVar1 != (MultGMission *)0x0) {
    pMVar1 = MultGMission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
