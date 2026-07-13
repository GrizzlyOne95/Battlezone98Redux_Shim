/*
 * Entry: 00539b7a
 * Name: SniperShellClass::SniperShellClass
 * Namespace: SniperShellClass
 * Signature: SniperShellClass * SniperShellClass(SniperShellClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperShellClass * __thiscall SniperShellClass::SniperShellClass(SniperShellClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->killLength = 3.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x534e4950;
  this->killRadius = 1.0;
  this->_padding_ = (int)"snipershell";
  return this;
}
