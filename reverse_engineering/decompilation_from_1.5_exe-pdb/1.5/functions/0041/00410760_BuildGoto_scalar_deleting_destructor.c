/*
 * Entry: 00410760
 * Name: BuildGoto::`scalar_deleting_destructor'
 * Namespace: BuildGoto
 * Signature: void * `scalar_deleting_destructor'(BuildGoto * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BuildGoto::_scalar_deleting_destructor_(BuildGoto *this,uint param_1)

{
  ~BuildGoto(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
