/*
 * Entry: 0040180d
 * Name: std::logic_error::`scalar_deleting_destructor'
 * Namespace: std::logic_error
 * Signature: void * `scalar_deleting_destructor'(logic_error * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall std::logic_error::_scalar_deleting_destructor_(logic_error *this,uint param_1)

{
  ~logic_error(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
