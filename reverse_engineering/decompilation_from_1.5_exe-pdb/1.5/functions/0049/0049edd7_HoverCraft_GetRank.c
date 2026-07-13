/*
 * Entry: 0049edd7
 * Name: HoverCraft::GetRank
 * Namespace: HoverCraft
 * Signature: float GetRank(HoverCraft * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall HoverCraft::GetRank(HoverCraft *this,float param_1,float param_2)

{
  Carrier *this_00;
  float fVar1;
  Weapon *pWVar2;
  int iVar3;
  float10 fVar4;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = param_1 - (float)this->_padding_;
  if ((float)this->_padding_ < 0.0) {
    fVar1 = fVar1 + 10.0;
  }
  param_1 = (250.0 - param_2) * 0.004 * 5.0 + fVar1;
  fVar4 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar4 == (float10)(float)this->_padding_) || (250.0 <= param_2)) {
    if ((this->_padding_ != 0) || (0.0001 <= (float)this->_padding_)) goto LAB_0049ee90;
    param_1 = param_1 - 5.0;
    fVar1 = 0.0;
    if (0.0 <= param_1) goto LAB_0049ee90;
  }
  else {
    fVar1 = param_1 + 1.0;
  }
  param_1 = fVar1;
LAB_0049ee90:
  if ((GameObject *)&this[-1].last_steer == GameObject::userObject) {
    param_1 = param_1 + 0.2;
  }
  this_00 = (Carrier *)this->_padding_;
  if (this_00 != (Carrier *)0x0) {
    iVar3 = 0;
    do {
      pWVar2 = Carrier::GetWeapon(this_00,iVar3);
      if ((pWVar2 != (Weapon *)0x0) &&
         ((float)this->_padding_ < pWVar2->fLastTriggered !=
          ((float)this->_padding_ == pWVar2->fLastTriggered))) {
        param_1 = param_1 + 1.0;
        break;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
  }
  iVar3 = this->_padding_;
  fVar1 = this->lastThrot - *(float *)(iVar3 + 0xcc);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = (float)this->soundThrust - *(float *)(iVar3 + 0xc4);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = (float)this->soundTurbo - *(float *)(iVar3 + 200);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  fVar1 = this->lastFly - *(float *)(iVar3 + 0xd0);
  if ((0.1 < fVar1) || (fVar1 < -0.1)) {
    param_1 = param_1 + 0.1;
  }
  if ((this->omegaEye).x != *(float *)(iVar3 + 0xd8)) {
    param_1 = param_1 + 0.1;
  }
  if ((this->omegaEye).y != *(float *)(iVar3 + 0xd4)) {
    param_1 = param_1 + 0.1;
  }
  if ((this->omegaEye).z != *(float *)(iVar3 + 0xdc)) {
    param_1 = param_1 + 0.1;
  }
  return param_1;
}
