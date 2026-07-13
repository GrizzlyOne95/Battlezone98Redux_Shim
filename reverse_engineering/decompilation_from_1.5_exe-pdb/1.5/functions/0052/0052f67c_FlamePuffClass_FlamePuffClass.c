/*
 * Entry: 0052f67c
 * Name: FlamePuffClass::FlamePuffClass
 * Namespace: FlamePuffClass
 * Signature: FlamePuffClass * FlamePuffClass(FlamePuffClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlamePuffClass * __thiscall FlamePuffClass::FlamePuffClass(FlamePuffClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->flameFirst = 0;
  this->flameRadius = 1.0;
  this->flameLast = 0;
  this->frameDelay = 0.2;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x464c414d;
  this->_padding_ = (int)"flamepuff";
  return this;
}
