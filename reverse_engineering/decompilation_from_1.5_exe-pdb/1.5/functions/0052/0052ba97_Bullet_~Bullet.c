/*
 * Entry: 0052ba97
 * Name: Bullet::~Bullet
 * Namespace: Bullet
 * Signature: void ~Bullet(Bullet * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bullet::~Bullet(Bullet *this)

{
  this->_padding_ = (int)&_vftable_;
  Ordnance::~Ordnance((Ordnance *)this);
  return;
}
