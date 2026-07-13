/*
 * Entry: 00531f74
 * Name: Missile::~Missile
 * Namespace: Missile
 * Signature: void ~Missile(Missile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::~Missile(Missile *this)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  return;
}
