/*
 * Entry: 0052c368
 * Name: Cannon::~Cannon
 * Namespace: Cannon
 * Signature: void ~Cannon(Cannon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Cannon::~Cannon(Cannon *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
