/*
 * Entry: 004aca4f
 * Name: ProducerClass::`scalar_deleting_destructor'
 * Namespace: ProducerClass
 * Signature: void * `scalar_deleting_destructor'(ProducerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ProducerClass::_scalar_deleting_destructor_(ProducerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
