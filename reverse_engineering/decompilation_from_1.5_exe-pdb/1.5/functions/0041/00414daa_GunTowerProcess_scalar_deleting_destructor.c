/*
 * Entry: 00414daa
 * Name: GunTowerProcess::`scalar_deleting_destructor'
 * Namespace: GunTowerProcess
 * Signature: void * `scalar_deleting_destructor'(GunTowerProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GunTowerProcess::_scalar_deleting_destructor_(GunTowerProcess *this,uint param_1)

{
  ~GunTowerProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
