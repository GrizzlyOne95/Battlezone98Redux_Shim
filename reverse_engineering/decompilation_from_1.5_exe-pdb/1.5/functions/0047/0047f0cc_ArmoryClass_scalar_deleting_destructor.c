/*
 * Entry: 0047f0cc
 * Name: ArmoryClass::`scalar_deleting_destructor'
 * Namespace: ArmoryClass
 * Signature: void * `scalar_deleting_destructor'(ArmoryClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ArmoryClass::_scalar_deleting_destructor_(ArmoryClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
