/*
 * Entry: 004be360
 * Name: BettyVoice::AmmoWarning
 * Namespace: BettyVoice
 * Signature: void AmmoWarning(BettyVoice * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::AmmoWarning(BettyVoice *this,GameObject *param_1)

{
  long lVar1;
  int iVar2;
  VoiceEvent VVar3;
  
  lVar1 = GameObject::userTeamNumber;
  if (param_1 == GameObject::userObject) {
    VVar3 = USER_AMMO_DEPLETED;
  }
  else {
    iVar2 = (**(code **)(param_1->_padding_ + 4))();
    if (iVar2 != lVar1) {
      return;
    }
    VVar3 = UNIT_AMMO_DEPLETED;
  }
  QueueVoice(this,VVar3);
  return;
}
