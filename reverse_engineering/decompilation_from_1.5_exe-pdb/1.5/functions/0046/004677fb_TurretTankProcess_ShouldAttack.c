/*
 * Entry: 004677fb
 * Name: TurretTankProcess::ShouldAttack
 * Namespace: TurretTankProcess
 * Signature: bool ShouldAttack(TurretTankProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::ShouldAttack(TurretTankProcess *this,State param_1)

{
  long lVar1;
  bool bVar2;
  int iVar3;
  
  lVar1 = GameObject::userTeamNumber;
  if ((this->_padding_ == 0) && (param_1 != WAIT)) {
    bVar2 = false;
  }
  else {
    iVar3 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
    if (iVar3 == lVar1) {
      bVar2 = FriendShouldAttack(this);
    }
    else {
      bVar2 = EnemyShouldAttack(this);
    }
  }
  return bVar2;
}
