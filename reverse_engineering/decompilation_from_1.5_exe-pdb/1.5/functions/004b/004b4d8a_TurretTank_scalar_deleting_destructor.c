/*
 * Entry: 004b4d8a
 * Name: TurretTank::`scalar_deleting_destructor'
 * Namespace: TurretTank
 * Signature: void * `scalar_deleting_destructor'(TurretTank * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TurretTank::_scalar_deleting_destructor_(TurretTank *this,uint param_1)

{
  ~TurretTank(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
