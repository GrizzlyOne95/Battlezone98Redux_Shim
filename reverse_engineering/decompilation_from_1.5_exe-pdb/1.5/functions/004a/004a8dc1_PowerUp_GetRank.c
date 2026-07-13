/*
 * Entry: 004a8dc1
 * Name: PowerUp::GetRank
 * Namespace: PowerUp
 * Signature: float GetRank(PowerUp * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall PowerUp::GetRank(PowerUp *this,float param_1,float param_2)

{
  float10 fVar1;
  float local_8;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  local_8 = -1.0;
  fVar1 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if (fVar1 == (float10)(float)this->_padding_) {
    if (((((*(byte *)(this->_padding_ + 0x10c) & 4) != 0) || (0.01 < (float)this->_padding_)) ||
        (0.01 < ABS((float)this->_padding_))) ||
       ((0.01 < ABS((float)this->_padding_) || (0.01 < ABS((float)this->_padding_))))) {
      local_8 = param_1 - (float)this->_padding_;
    }
  }
  else {
    local_8 = (param_1 - (float)this->_padding_) + 1.0;
  }
  fVar1 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar1 < (float10)0.0) || ((*(uint *)(this->_padding_ + 0x14) & 0x1000200) != 0)) {
    local_8 = local_8 + 10.0;
  }
  return local_8;
}
