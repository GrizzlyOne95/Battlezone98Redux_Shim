/*
 * Entry: 004acf20
 * Name: RecyclerClass::`scalar_deleting_destructor'
 * Namespace: RecyclerClass
 * Signature: void * `scalar_deleting_destructor'(RecyclerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RecyclerClass::_scalar_deleting_destructor_(RecyclerClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
