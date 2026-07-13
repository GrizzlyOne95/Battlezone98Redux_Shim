/*
 * Entry: 005322ff
 * Name: MissileClass::~MissileClass
 * Namespace: MissileClass
 * Signature: void ~MissileClass(MissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MissileClass::~MissileClass(MissileClass *this)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  return;
}
