/*
 * Entry: 00482b47
 * Name: Building::GetRank
 * Namespace: Building
 * Signature: float GetRank(Building * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Building::GetRank(Building *this,float param_1,float param_2)

{
  float fVar1;
  float10 fVar2;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = param_1 - (float)this->_padding_;
  fVar2 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar2 == (float10)(float)this->_padding_) || (250.0 <= param_2)) {
    fVar2 = (float10)(**(code **)(this->_padding_ + 0x1c))();
    if ((float10)0.0 <= fVar2) {
      fVar1 = -1.0;
    }
    else {
      fVar1 = fVar1 + 10.0;
    }
  }
  else {
    fVar1 = fVar1 + 5.0;
  }
  return fVar1;
}
