/*
 * Entry: 004a8e9a
 * Name: PowerUp::PermStateChanged
 * Namespace: PowerUp
 * Signature: bool PermStateChanged(PowerUp * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PowerUp::PermStateChanged(PowerUp *this,float param_1)

{
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  return (float)this->_padding_ + 10.0 < param_1;
}
