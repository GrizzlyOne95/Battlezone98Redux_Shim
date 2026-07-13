/*
 * Entry: 005491b0
 * Name: OldNew::`scalar_deleting_destructor'
 * Namespace: OldNew
 * Signature: void * `scalar_deleting_destructor'(OldNew * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall OldNew::_scalar_deleting_destructor_(OldNew *this,uint param_1)

{
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
