/*
 * Entry: 0044d252
 * Name: MultSTMission::CreateObject
 * Namespace: MultSTMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MultSTMission::CreateObject(void)

{
  MultSTMission *pMVar1;
  
  pMVar1 = operator_new(0x70);
  if (pMVar1 != (MultSTMission *)0x0) {
    pMVar1 = MultSTMission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
