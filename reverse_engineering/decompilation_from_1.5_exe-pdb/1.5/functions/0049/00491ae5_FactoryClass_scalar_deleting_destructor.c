/*
 * Entry: 00491ae5
 * Name: FactoryClass::`scalar_deleting_destructor'
 * Namespace: FactoryClass
 * Signature: void * `scalar_deleting_destructor'(FactoryClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FactoryClass::_scalar_deleting_destructor_(FactoryClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
