/*
 * Entry: 00467a8d
 * Name: TurretBlastAttack::`scalar_deleting_destructor'
 * Namespace: TurretBlastAttack
 * Signature: void * `scalar_deleting_destructor'(TurretBlastAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TurretBlastAttack::_scalar_deleting_destructor_(TurretBlastAttack *this,uint param_1)

{
  ~TurretBlastAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
