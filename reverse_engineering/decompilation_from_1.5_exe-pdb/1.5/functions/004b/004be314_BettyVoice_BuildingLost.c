/*
 * Entry: 004be314
 * Name: BettyVoice::BuildingLost
 * Namespace: BettyVoice
 * Signature: void BuildingLost(BettyVoice * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::BuildingLost(BettyVoice *this,GameObject *param_1)

{
  long lVar1;
  int iVar2;
  int iVar3;
  VoiceEvent VVar4;
  
  lVar1 = GameObject::userTeamNumber;
  iVar2 = (**(code **)(param_1->_padding_ + 4))();
  if (iVar2 == lVar1) {
    iVar2 = param_1->teamSlot;
    iVar3 = (**(code **)param_1->_padding_)();
    if (*(int *)(iVar3 + 0x28) == 2) {
      if (iVar2 - 0x2dU < 10) {
        VVar4 = BLDG_LOST_POWERPLANT;
      }
      else {
        VVar4 = BLDG_LOST_GENERIC;
      }
      QueueVoice(this,VVar4);
    }
  }
  return;
}
