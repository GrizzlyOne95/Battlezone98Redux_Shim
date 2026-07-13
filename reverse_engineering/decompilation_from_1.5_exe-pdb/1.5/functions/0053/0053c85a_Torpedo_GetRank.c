/*
 * Entry: 0053c85a
 * Name: Torpedo::GetRank
 * Namespace: Torpedo
 * Signature: float GetRank(Torpedo * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Torpedo::GetRank(Torpedo *this,float param_1,float param_2)

{
  float fVar1;
  float10 fVar2;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = (param_1 - (float)this->_padding_) + 1.0;
  if ((float)this->_padding_ < 0.0) {
    fVar1 = fVar1 + 10.0;
  }
  param_1 = (250.0 - param_2) * 0.004 * 5.0 + fVar1;
  fVar2 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar2 != (float10)(float)this->_padding_) && (param_2 < 250.0)) {
    param_1 = param_1 + 1.0;
  }
  return param_1;
}
