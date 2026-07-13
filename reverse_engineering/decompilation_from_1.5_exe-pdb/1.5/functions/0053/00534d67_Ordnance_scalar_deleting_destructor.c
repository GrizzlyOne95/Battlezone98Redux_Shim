/*
 * Entry: 00534d67
 * Name: Ordnance::`scalar_deleting_destructor'
 * Namespace: Ordnance
 * Signature: void * `scalar_deleting_destructor'(Ordnance * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Ordnance::_scalar_deleting_destructor_(Ordnance *this,uint param_1)

{
  ~Ordnance(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
