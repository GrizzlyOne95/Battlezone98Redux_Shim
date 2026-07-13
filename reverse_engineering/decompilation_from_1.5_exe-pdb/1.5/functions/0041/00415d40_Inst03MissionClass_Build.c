/*
 * Entry: 00415d40
 * Name: Inst03MissionClass::Build
 * Namespace: Inst03MissionClass
 * Signature: AiMission * Build(Inst03MissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall Inst03MissionClass::Build(Inst03MissionClass *this)

{
  Inst03Mission *pIVar1;
  
  pIVar1 = operator_new(0x4c);
  if (pIVar1 != (Inst03Mission *)0x0) {
    pIVar1 = Inst03Mission::Inst03Mission(pIVar1);
    return (AiMission *)pIVar1;
  }
  return (AiMission *)0x0;
}
