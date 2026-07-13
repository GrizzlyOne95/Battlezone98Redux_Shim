/*
 * Entry: 00414f9d
 * Name: GunTowerEnemy::`scalar_deleting_destructor'
 * Namespace: GunTowerEnemy
 * Signature: void * `scalar_deleting_destructor'(GunTowerEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GunTowerEnemy::_scalar_deleting_destructor_(GunTowerEnemy *this,uint param_1)

{
  GunTowerProcess::~GunTowerProcess((GunTowerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
