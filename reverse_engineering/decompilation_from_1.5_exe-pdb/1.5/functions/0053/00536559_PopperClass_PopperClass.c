/*
 * Entry: 00536559
 * Name: PopperClass::PopperClass
 * Namespace: PopperClass
 * Signature: PopperClass * PopperClass(PopperClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PopperClass * __thiscall PopperClass::PopperClass(PopperClass *this)

{
  GrenadeClass::GrenadeClass((GrenadeClass *)this);
  this->launchOrd = (OrdnanceClass *)0x0;
  this->scanRange = 100.0;
  this->launchXpl = (ExplosionClass *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x504f5052;
  this->_padding_ = (int)"popper";
  this->_padding_ = 10;
  return this;
}
