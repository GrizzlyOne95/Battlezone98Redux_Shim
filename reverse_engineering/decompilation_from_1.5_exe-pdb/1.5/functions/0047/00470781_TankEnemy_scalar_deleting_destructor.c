/*
 * Entry: 00470781
 * Name: TankEnemy::`scalar_deleting_destructor'
 * Namespace: TankEnemy
 * Signature: void * `scalar_deleting_destructor'(TankEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TankEnemy::_scalar_deleting_destructor_(TankEnemy *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
