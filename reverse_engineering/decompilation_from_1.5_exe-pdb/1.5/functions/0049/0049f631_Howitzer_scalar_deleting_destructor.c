/*
 * Entry: 0049f631
 * Name: Howitzer::`scalar_deleting_destructor'
 * Namespace: Howitzer
 * Signature: void * `scalar_deleting_destructor'(Howitzer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Howitzer::_scalar_deleting_destructor_(Howitzer *this,uint param_1)

{
  TurretTank::~TurretTank((TurretTank *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
