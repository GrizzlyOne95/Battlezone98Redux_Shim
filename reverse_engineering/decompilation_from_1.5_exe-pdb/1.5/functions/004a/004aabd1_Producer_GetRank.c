/*
 * Entry: 004aabd1
 * Name: Producer::GetRank
 * Namespace: Producer
 * Signature: float GetRank(Producer * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Producer::GetRank(Producer *this,float param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  fVar1 = (param_1 - (float)this->_padding_) + (250.0 - param_2) * 0.004 * 5.0;
  fVar3 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar3 != (float10)(float)this->_padding_) && (param_2 < 250.0)) {
    fVar1 = fVar1 + 1.0;
  }
  if (0.0 < (float)this->_padding_) {
    fVar2 = fVar1;
    if (this->_padding_ == 2) {
      fVar2 = 0.0;
      if (0.0 <= fVar1 - 5.0) {
        return fVar1 - 5.0;
      }
    }
  }
  else {
    fVar2 = fVar1 + 10.0;
  }
  return fVar2;
}
