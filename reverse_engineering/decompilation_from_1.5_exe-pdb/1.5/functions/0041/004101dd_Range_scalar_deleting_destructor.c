/*
 * Entry: 004101dd
 * Name: Range::`scalar_deleting_destructor'
 * Namespace: Range
 * Signature: void * `scalar_deleting_destructor'(Range * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Range::_scalar_deleting_destructor_(Range *this,uint param_1)

{
  ~Range(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
