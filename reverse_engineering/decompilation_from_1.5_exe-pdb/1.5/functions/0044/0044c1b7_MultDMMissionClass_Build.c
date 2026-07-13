/*
 * Entry: 0044c1b7
 * Name: MultDMMissionClass::Build
 * Namespace: MultDMMissionClass
 * Signature: AiMission * Build(MultDMMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall MultDMMissionClass::Build(MultDMMissionClass *this)

{
  MultDMMission *pMVar1;
  
  pMVar1 = operator_new(0x70);
  if (pMVar1 != (MultDMMission *)0x0) {
    pMVar1 = MultDMMission::MultDMMission(pMVar1);
    return (AiMission *)pMVar1;
  }
  return (AiMission *)0x0;
}
