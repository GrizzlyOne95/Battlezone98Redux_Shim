/*
 * Entry: 0053a4d9
 * Name: SprayBombClass::SprayBombClass
 * Namespace: SprayBombClass
 * Signature: SprayBombClass * SprayBombClass(SprayBombClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBombClass * __thiscall SprayBombClass::SprayBombClass(SprayBombClass *this)

{
  GrenadeClass::GrenadeClass((GrenadeClass *)this);
  this->sprayClass = (GameObjectClass *)0x0;
  this->bounceRatio = 0.5;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53424d42;
  this->_padding_ = (int)"spraybomb";
  strncpy(this->soundBounce,"bounce.wav",0x10);
  return this;
}
