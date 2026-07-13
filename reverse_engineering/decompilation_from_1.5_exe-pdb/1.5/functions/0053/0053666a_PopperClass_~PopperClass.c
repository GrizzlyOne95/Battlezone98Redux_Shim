/*
 * Entry: 0053666a
 * Name: PopperClass::~PopperClass
 * Namespace: PopperClass
 * Signature: void ~PopperClass(PopperClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PopperClass::~PopperClass(PopperClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  return;
}
