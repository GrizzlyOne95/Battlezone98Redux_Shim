/*
 * Entry: 0052f6e8
 * Name: FlamePuff::~FlamePuff
 * Namespace: FlamePuff
 * Signature: void ~FlamePuff(FlamePuff * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlamePuff::~FlamePuff(FlamePuff *this)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
