/*
 * Entry: 004b0adf
 * Name: SObject::`scalar_deleting_destructor'
 * Namespace: SObject
 * Signature: void * `scalar_deleting_destructor'(SObject * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SObject::_scalar_deleting_destructor_(SObject *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
