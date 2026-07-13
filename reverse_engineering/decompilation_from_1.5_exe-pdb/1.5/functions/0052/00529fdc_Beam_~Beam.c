/*
 * Entry: 00529fdc
 * Name: Beam::~Beam
 * Namespace: Beam
 * Signature: void ~Beam(Beam * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Beam::~Beam(Beam *this)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
