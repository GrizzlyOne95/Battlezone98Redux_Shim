/*
 * Entry: 0052ad84
 * Name: Bolt::~Bolt
 * Namespace: Bolt
 * Signature: void ~Bolt(Bolt * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bolt::~Bolt(Bolt *this)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
