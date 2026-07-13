/*
 * Entry: 004be3ae
 * Name: BettyVoice::AttackWarning
 * Namespace: BettyVoice
 * Signature: void AttackWarning(BettyVoice * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BettyVoice::AttackWarning(BettyVoice *this,GameObject *param_1)

{
  long lVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  lVar1 = GameObject::userTeamNumber;
  iVar2 = (**(code **)(param_1->_padding_ + 4))();
  if ((iVar2 == lVar1) && (fVar4 = Get_Time(), this->nextAttack <= fVar4)) {
    fVar4 = Get_Time();
    this->nextAttack = fVar4 + 30.0;
    iVar2 = param_1->teamSlot;
    iVar3 = (**(code **)param_1->_padding_)();
    iVar3 = *(int *)(iVar3 + 0x28);
    if ((iVar3 == 6) || (iVar3 == 1)) {
      if ((((iVar2 != 1) && (iVar2 != 2)) && (iVar2 != 3)) && (9 < iVar2 - 0x50U)) {
        return;
      }
    }
    else if (iVar3 != 2) {
      return;
    }
    QueueVoice(this,BASE_UNDER_ATTACK);
  }
  return;
}
