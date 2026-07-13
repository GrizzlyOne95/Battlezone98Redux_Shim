/*
 * Entry: 00415aad
 * Name: Inst01MissionClass::Build
 * Namespace: Inst01MissionClass
 * Signature: AiMission * Build(Inst01MissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall Inst01MissionClass::Build(Inst01MissionClass *this)

{
  Inst01Mission *pIVar1;
  
  pIVar1 = operator_new(0x48);
  if (pIVar1 != (Inst01Mission *)0x0) {
    pIVar1 = Inst01Mission::Inst01Mission(pIVar1);
    return (AiMission *)pIVar1;
  }
  return (AiMission *)0x0;
}
