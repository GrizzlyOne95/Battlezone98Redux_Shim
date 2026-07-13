/*
 * Entry: 00416197
 * Name: Inst4XMission::PostLoad
 * Namespace: Inst4XMission
 * Signature: bool PostLoad(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst4XMission::PostLoad(Inst4XMission *this)

{
  bool bVar1;
  int iVar2;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  iVar2 = ConvertHandle((this->field21_0x5c)._s_0.handle_1);
  (this->field21_0x5c)._s_0.handle_1 = iVar2;
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
