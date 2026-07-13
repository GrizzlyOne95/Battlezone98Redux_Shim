/*
 * Entry: 0040c1e4
 * Name: APCAttack::`scalar_deleting_destructor'
 * Namespace: APCAttack
 * Signature: void * `scalar_deleting_destructor'(APCAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APCAttack::_scalar_deleting_destructor_(APCAttack *this,uint param_1)

{
  ~APCAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
