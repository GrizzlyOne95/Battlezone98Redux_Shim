/*
 * Entry: 00470b57
 * Name: RocketTankEnemy::`scalar_deleting_destructor'
 * Namespace: RocketTankEnemy
 * Signature: void * `scalar_deleting_destructor'(RocketTankEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RocketTankEnemy::_scalar_deleting_destructor_(RocketTankEnemy *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
