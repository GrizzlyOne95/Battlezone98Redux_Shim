/*
 * Entry: 00415c32
 * Name: Inst02MissionClass::Build
 * Namespace: Inst02MissionClass
 * Signature: AiMission * Build(Inst02MissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall Inst02MissionClass::Build(Inst02MissionClass *this)

{
  Inst02Mission *pIVar1;
  
  pIVar1 = operator_new(0x48);
  if (pIVar1 != (Inst02Mission *)0x0) {
    pIVar1 = Inst02Mission::Inst02Mission(pIVar1);
    return (AiMission *)pIVar1;
  }
  return (AiMission *)0x0;
}
