/*
 * Entry: 00530948
 * Name: Launcher::Control
 * Namespace: Launcher
 * Signature: void Control(Launcher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Launcher::Control(Launcher *this,float param_1)

{
  bool bVar1;
  GameObject *this_00;
  GameObject *pGVar2;
  int iVar3;
  GameObject *local_8;
  
  Weapon::Control((Weapon *)this,param_1);
  if ((this->triggered == false) || (bVar1 = Weapon::PermissionToFire((Weapon *)this), !bVar1)) {
    iVar3 = *(int *)(this->_padding_ + 0x68);
    this->lockTimer = 0.0;
    this->curTarget = 0;
    this->lockState = 0;
  }
  else {
    this_00 = (GameObject *)(**(code **)(this->_padding_ + 0x34))(param_1);
    pGVar2 = GameObject::GetObj(this->curTarget);
    local_8 = GameObject::GetObj(this->lockTarget);
    if (pGVar2 == (GameObject *)0x0) {
      this->curTarget = 0;
    }
    if (local_8 == (GameObject *)0x0) {
      this->lockTarget = 0;
    }
    if ((this_00 == pGVar2) || ((this_00 == local_8 && (this_00 != (GameObject *)0x0)))) {
      if (pGVar2 != (GameObject *)0x0) {
        (**(code **)(this->_padding_ + 0x38))(pGVar2,param_1);
      }
    }
    else {
      if (this_00 == (GameObject *)0x0) {
        iVar3 = 0;
      }
      else {
        iVar3 = GameObject::GetHandle(this_00);
      }
      this->lockState = 0;
      this->lockTimer = 0.0;
      this->curTarget = iVar3;
      pGVar2 = this_00;
    }
    while (this->lockTimer < 0.0) {
      if (this->lockState < 1) {
        this->lockTimer = 0.0;
      }
      else {
        this->lockState = this->lockState + -1;
        this->lockTimer = this->lockDelay + this->lockTimer;
      }
    }
    if (this->lockDelay < this->lockTimer) {
      do {
        if (*(int *)(this->_padding_ + 0xb4) + -1 <= this->lockState) break;
        iVar3 = this->lockState + 1;
        this->lockState = iVar3;
        this->lockTimer = this->lockTimer - this->lockDelay;
        if (iVar3 == *(int *)(this->_padding_ + 0xb4) + -1) {
          this->lockTarget = this->curTarget;
          local_8 = pGVar2;
        }
      } while (this->lockDelay < this->lockTimer);
    }
    iVar3 = this->_padding_;
    if (pGVar2 == (GameObject *)0x0) {
      if (local_8 == (GameObject *)0x0) {
        iVar3 = *(int *)(iVar3 + 0x68);
      }
      else {
        iVar3 = *(int *)(*(int *)(iVar3 + 0xb8) + -4 + *(int *)(iVar3 + 0xb4) * 4);
      }
    }
    else {
      iVar3 = *(int *)(*(int *)(iVar3 + 0xb8) + this->lockState * 4);
    }
  }
  this->_padding_ = iVar3;
  return;
}
