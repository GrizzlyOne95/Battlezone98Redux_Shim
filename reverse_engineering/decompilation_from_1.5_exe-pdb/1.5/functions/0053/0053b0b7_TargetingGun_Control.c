/*
 * Entry: 0053b0b7
 * Name: TargetingGun::Control
 * Namespace: TargetingGun
 * Signature: void Control(TargetingGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetingGun::Control(TargetingGun *this,float param_1)

{
  int iVar1;
  GameObject *pGVar2;
  
  Weapon::Control((Weapon *)this,param_1);
  if (this->leaderObj == (LeaderRound *)0x0) {
    this->_padding_ = *(int *)(this->_padding_ + 0x68);
  }
  else {
    pGVar2 = GameObject::GetObj(this->leaderObj->hitObj);
    if (pGVar2 == (GameObject *)0x0) {
      iVar1 = *(int *)(this->_padding_ + 0x9c);
      this->lockTarget = (GameObject *)0x0;
      this->_padding_ = iVar1;
    }
    else {
      iVar1 = this->_padding_;
      this->_padding_ = *(int *)(iVar1 + 0xa0);
      if (this->lockTarget != pGVar2) {
        this->lockTarget = pGVar2;
        this->salvoCount = *(int *)(iVar1 + 0x98);
        this->shotTimer = -*(float *)(iVar1 + 0x90);
      }
    }
  }
  return;
}
