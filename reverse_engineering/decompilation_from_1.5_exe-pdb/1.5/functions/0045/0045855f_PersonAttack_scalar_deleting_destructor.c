/*
 * Entry: 0045855f
 * Name: PersonAttack::`scalar_deleting_destructor'
 * Namespace: PersonAttack
 * Signature: void * `scalar_deleting_destructor'(PersonAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonAttack::_scalar_deleting_destructor_(PersonAttack *this,uint param_1)

{
  ~PersonAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
