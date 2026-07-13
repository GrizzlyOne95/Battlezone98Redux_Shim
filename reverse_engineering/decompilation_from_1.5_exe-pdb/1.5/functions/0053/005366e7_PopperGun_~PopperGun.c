/*
 * Entry: 005366e7
 * Name: PopperGun::~PopperGun
 * Namespace: PopperGun
 * Signature: void ~PopperGun(PopperGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PopperGun::~PopperGun(PopperGun *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
