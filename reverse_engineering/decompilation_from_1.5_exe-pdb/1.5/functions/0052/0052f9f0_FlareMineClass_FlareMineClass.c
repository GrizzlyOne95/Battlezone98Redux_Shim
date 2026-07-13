/*
 * Entry: 0052f9f0
 * Name: FlareMineClass::FlareMineClass
 * Namespace: FlareMineClass
 * Signature: FlareMineClass * FlareMineClass(FlareMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlareMineClass * __thiscall FlareMineClass::FlareMineClass(FlareMineClass *this)

{
  MineClass::MineClass((MineClass *)this);
  this->payloadClass = (OrdnanceClass *)0x0;
  this->_padding_ = 0x42700000;
  this->_padding_ = (int)&_vftable_;
  this->shotDelay = 0.05;
  this->_padding_ = 0x464c4152;
  this->_padding_ = (int)"flare";
  this->shotVariance = 0.5;
  this->fireSound[0] = '\0';
  return this;
}
