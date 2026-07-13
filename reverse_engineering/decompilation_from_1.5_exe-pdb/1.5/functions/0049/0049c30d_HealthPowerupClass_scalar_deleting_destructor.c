/*
 * Entry: 0049c30d
 * Name: HealthPowerupClass::`scalar_deleting_destructor'
 * Namespace: HealthPowerupClass
 * Signature: void * `scalar_deleting_destructor'(HealthPowerupClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
HealthPowerupClass::_scalar_deleting_destructor_(HealthPowerupClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
