/*
 * Entry: 004150f5
 * Name: GunTowerAttack::`scalar_deleting_destructor'
 * Namespace: GunTowerAttack
 * Signature: void * `scalar_deleting_destructor'(GunTowerAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GunTowerAttack::_scalar_deleting_destructor_(GunTowerAttack *this,uint param_1)

{
  ~GunTowerAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
