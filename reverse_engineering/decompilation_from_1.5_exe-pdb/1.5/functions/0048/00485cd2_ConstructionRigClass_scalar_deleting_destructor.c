/*
 * Entry: 00485cd2
 * Name: ConstructionRigClass::`scalar_deleting_destructor'
 * Namespace: ConstructionRigClass
 * Signature: void * `scalar_deleting_destructor'(ConstructionRigClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ConstructionRigClass::_scalar_deleting_destructor_(ConstructionRigClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
