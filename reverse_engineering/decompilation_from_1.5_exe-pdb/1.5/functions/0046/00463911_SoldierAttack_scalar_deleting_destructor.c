/*
 * Entry: 00463911
 * Name: SoldierAttack::`scalar_deleting_destructor'
 * Namespace: SoldierAttack
 * Signature: void * `scalar_deleting_destructor'(SoldierAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierAttack::_scalar_deleting_destructor_(SoldierAttack *this,uint param_1)

{
  ~SoldierAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
