/*
 * Entry: 0040563c
 * Name: std::out_of_range::`scalar_deleting_destructor'
 * Namespace: std::out_of_range
 * Signature: void * `scalar_deleting_destructor'(out_of_range * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall std::out_of_range::_scalar_deleting_destructor_(out_of_range *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  logic_error::~logic_error((logic_error *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
