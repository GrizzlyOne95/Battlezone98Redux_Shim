/*
 * Entry: 00537e82
 * Name: Rocket::~Rocket
 * Namespace: Rocket
 * Signature: void ~Rocket(Rocket * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Rocket::~Rocket(Rocket *this)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
