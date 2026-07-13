/*
 * Entry: 00401855
 * Name: std::length_error::`scalar_deleting_destructor'
 * Namespace: std::length_error
 * Signature: void * `scalar_deleting_destructor'(length_error * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall std::length_error::_scalar_deleting_destructor_(length_error *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  logic_error::~logic_error((logic_error *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
