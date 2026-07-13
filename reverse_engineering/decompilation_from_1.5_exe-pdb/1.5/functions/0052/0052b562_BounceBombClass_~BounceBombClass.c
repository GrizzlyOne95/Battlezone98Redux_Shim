/*
 * Entry: 0052b562
 * Name: BounceBombClass::~BounceBombClass
 * Namespace: BounceBombClass
 * Signature: void ~BounceBombClass(BounceBombClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BounceBombClass::~BounceBombClass(BounceBombClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  return;
}
