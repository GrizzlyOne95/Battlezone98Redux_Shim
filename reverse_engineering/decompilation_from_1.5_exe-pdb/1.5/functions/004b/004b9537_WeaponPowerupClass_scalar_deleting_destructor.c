/*
 * Entry: 004b9537
 * Name: WeaponPowerupClass::`scalar_deleting_destructor'
 * Namespace: WeaponPowerupClass
 * Signature: void * `scalar_deleting_destructor'(WeaponPowerupClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
WeaponPowerupClass::_scalar_deleting_destructor_(WeaponPowerupClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
