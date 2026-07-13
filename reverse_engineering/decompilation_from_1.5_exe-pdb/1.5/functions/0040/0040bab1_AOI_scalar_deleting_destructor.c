/*
 * Entry: 0040bab1
 * Name: AOI::`scalar_deleting_destructor'
 * Namespace: AOI
 * Signature: void * `scalar_deleting_destructor'(AOI * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AOI::_scalar_deleting_destructor_(AOI *this,uint param_1)

{
  ~AOI(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
