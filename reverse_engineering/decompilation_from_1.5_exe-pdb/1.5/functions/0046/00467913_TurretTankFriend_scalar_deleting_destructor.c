/*
 * Entry: 00467913
 * Name: TurretTankFriend::`scalar_deleting_destructor'
 * Namespace: TurretTankFriend
 * Signature: void * `scalar_deleting_destructor'(TurretTankFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TurretTankFriend::_scalar_deleting_destructor_(TurretTankFriend *this,uint param_1)

{
  TurretTankProcess::~TurretTankProcess((TurretTankProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
