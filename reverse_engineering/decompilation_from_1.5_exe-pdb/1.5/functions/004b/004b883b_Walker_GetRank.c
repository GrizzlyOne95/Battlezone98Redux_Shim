/*
 * Entry: 004b883b
 * Name: Walker::GetRank
 * Namespace: Walker
 * Signature: float GetRank(Walker * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Walker::GetRank(Walker *this,float param_1,float param_2)

{
  float fVar1;
  char cVar2;
  Weapon *pWVar3;
  int iVar4;
  float10 fVar5;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = param_1 - (float)this->_padding_;
  if ((float)this->_padding_ <= 0.0) {
    fVar1 = fVar1 + 10.0;
  }
  param_1 = (250.0 - param_2) * 0.004 * 5.0 + fVar1;
  fVar5 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar5 != (float10)(float)this->_padding_) && (param_2 < 250.0)) {
    param_1 = param_1 + 1.0;
  }
  if ((GameObject *)&this[-1].last_steer == GameObject::userObject) {
    param_1 = param_1 + 0.2;
  }
  if (this->_padding_ != 0) {
    iVar4 = 0;
    do {
      pWVar3 = Carrier::GetWeapon((Carrier *)this->_padding_,iVar4);
      if ((pWVar3 != (Weapon *)0x0) &&
         (cVar2 = (**(code **)(pWVar3->_padding_ + 0x10))(), cVar2 != '\0')) {
        param_1 = param_1 + 0.1;
        break;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 5);
  }
  iVar4 = this->_padding_;
  fVar1 = (float)this->_padding_ - *(float *)(iVar4 + 0xcc);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = (float)this->_padding_ - *(float *)(iVar4 + 0xc4);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = (float)this->_padding_ - *(float *)(iVar4 + 200);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = (float)this->_padding_ - *(float *)(iVar4 + 0xd0);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  if (this->curAnim != *(int *)(iVar4 + 0xd8)) {
    param_1 = param_1 + 0.1;
  }
  if (this->animHandle != *(int *)(iVar4 + 0xd4)) {
    param_1 = param_1 + 0.1;
  }
  if (*(int *)&this->cycleState != *(int *)(iVar4 + 0xdc)) {
    param_1 = param_1 + 0.1;
  }
  return param_1;
}
