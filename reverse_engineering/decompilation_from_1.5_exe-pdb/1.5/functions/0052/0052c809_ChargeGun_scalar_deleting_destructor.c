/*
 * Entry: 0052c809
 * Name: ChargeGun::`scalar_deleting_destructor'
 * Namespace: ChargeGun
 * Signature: void * `scalar_deleting_destructor'(ChargeGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ChargeGun::_scalar_deleting_destructor_(ChargeGun *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Cannon::~Cannon((Cannon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
