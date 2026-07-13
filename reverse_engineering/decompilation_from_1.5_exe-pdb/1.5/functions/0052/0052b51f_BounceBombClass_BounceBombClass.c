/*
 * Entry: 0052b51f
 * Name: BounceBombClass::BounceBombClass
 * Namespace: BounceBombClass
 * Signature: BounceBombClass * BounceBombClass(BounceBombClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BounceBombClass * __thiscall BounceBombClass::BounceBombClass(BounceBombClass *this)

{
  GrenadeClass::GrenadeClass((GrenadeClass *)this);
  this->bounceRatio = 0.5;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x42424d42;
  this->_padding_ = (int)"bouncebomb";
  strncpy(this->soundBounce,"bounce.wav",0x10);
  return this;
}
