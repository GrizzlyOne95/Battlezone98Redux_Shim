/*
 * Entry: 004162a8
 * Name: Inst4XMissionClass::Build
 * Namespace: Inst4XMissionClass
 * Signature: AiMission * Build(Inst4XMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall Inst4XMissionClass::Build(Inst4XMissionClass *this)

{
  Inst4XMission *pIVar1;
  
  pIVar1 = operator_new(0x6c);
  if (pIVar1 != (Inst4XMission *)0x0) {
    pIVar1 = Inst4XMission::Inst4XMission(pIVar1);
    return (AiMission *)pIVar1;
  }
  return (AiMission *)0x0;
}
