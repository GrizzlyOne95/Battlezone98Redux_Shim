/*
 * Entry: 0052f6b2
 * Name: FlamePuffClass::~FlamePuffClass
 * Namespace: FlamePuffClass
 * Signature: void ~FlamePuffClass(FlamePuffClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlamePuffClass::~FlamePuffClass(FlamePuffClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
