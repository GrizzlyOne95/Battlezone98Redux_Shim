/*
 * Entry: 004be2b5
 * Name: BettyVoice::VehicleLost
 * Namespace: BettyVoice
 * Signature: void VehicleLost(BettyVoice * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::VehicleLost(BettyVoice *this,GameObject *param_1)

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
    if (*(int *)(iVar3 + 0x20) == 0x53434156) {
      VVar4 = UNIT_LOST_SCAVENGER;
    }
    else if (iVar2 - 0xfU < 10) {
      VVar4 = UNIT_LOST_DEFENSIVE;
    }
    else if (iVar2 - 5U < 10) {
      VVar4 = UNIT_LOST_OFFENSIVE;
    }
    else {
      VVar4 = UNIT_LOST_GENERIC;
    }
    QueueVoice(this,VVar4);
  }
  return;
}
