/*
 * Entry: 0047f09b
 * Name: ArmoryClass::~ArmoryClass
 * Namespace: ArmoryClass
 * Signature: void ~ArmoryClass(ArmoryClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryClass::~ArmoryClass(ArmoryClass *this)

{
  this->_padding_ = (int)&_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  return;
}
