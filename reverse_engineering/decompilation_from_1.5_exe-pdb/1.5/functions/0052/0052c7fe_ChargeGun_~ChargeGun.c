/*
 * Entry: 0052c7fe
 * Name: ChargeGun::~ChargeGun
 * Namespace: ChargeGun
 * Signature: void ~ChargeGun(ChargeGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ChargeGun::~ChargeGun(ChargeGun *this)

{
  this->_padding_ = (int)&_vftable_;
  Cannon::~Cannon((Cannon *)this);
  return;
}
