/*
 * Entry: 004b3e61
 * Name: TurretCraft::GetRank
 * Namespace: TurretCraft
 * Signature: float GetRank(TurretCraft * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall TurretCraft::GetRank(TurretCraft *this,float param_1,float param_2)

{
  float fVar1;
  float10 fVar2;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = (param_1 - (float)this->_padding_) + (250.0 - param_2) * 0.004 * 5.0;
  fVar2 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar2 != (float10)(float)this->_padding_) && (param_2 < 250.0)) {
    fVar1 = fVar1 + 1.0;
  }
  if ((float)this->_padding_ <= 0.0) {
    fVar1 = fVar1 + 10.0;
  }
  return fVar1;
}
