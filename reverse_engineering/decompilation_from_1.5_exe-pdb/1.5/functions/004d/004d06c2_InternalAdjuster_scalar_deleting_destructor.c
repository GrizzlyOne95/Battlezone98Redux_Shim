/*
 * Entry: 004d06c2
 * Name: InternalAdjuster::`scalar_deleting_destructor'
 * Namespace: InternalAdjuster
 * Signature: void * `scalar_deleting_destructor'(InternalAdjuster * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
InternalAdjuster::_scalar_deleting_destructor_(InternalAdjuster *this,uint param_1)

{
  ~InternalAdjuster(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
