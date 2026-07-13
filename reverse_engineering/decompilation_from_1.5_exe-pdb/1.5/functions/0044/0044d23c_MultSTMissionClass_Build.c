/*
 * Entry: 0044d23c
 * Name: MultSTMissionClass::Build
 * Namespace: MultSTMissionClass
 * Signature: AiMission * Build(MultSTMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall MultSTMissionClass::Build(MultSTMissionClass *this)

{
  MultSTMission *pMVar1;
  
  pMVar1 = operator_new(0x70);
  if (pMVar1 != (MultSTMission *)0x0) {
    pMVar1 = MultSTMission::MultSTMission(pMVar1);
    return (AiMission *)pMVar1;
  }
  return (AiMission *)0x0;
}
