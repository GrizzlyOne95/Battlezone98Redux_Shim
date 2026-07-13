/*
 * Entry: 004131b6
 * Name: GechAttack::`scalar_deleting_destructor'
 * Namespace: GechAttack
 * Signature: void * `scalar_deleting_destructor'(GechAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GechAttack::_scalar_deleting_destructor_(GechAttack *this,uint param_1)

{
  ~GechAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
