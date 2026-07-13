/*
 * Entry: 00470e19
 * Name: RocketTankAttack::`scalar_deleting_destructor'
 * Namespace: RocketTankAttack
 * Signature: void * `scalar_deleting_destructor'(RocketTankAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RocketTankAttack::_scalar_deleting_destructor_(RocketTankAttack *this,uint param_1)

{
  ~RocketTankAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
