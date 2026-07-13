/*
 * Entry: 00467aa9
 * Name: TurretAttack::`scalar_deleting_destructor'
 * Namespace: TurretAttack
 * Signature: void * `scalar_deleting_destructor'(TurretAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TurretAttack::_scalar_deleting_destructor_(TurretAttack *this,uint param_1)

{
  ~TurretAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
