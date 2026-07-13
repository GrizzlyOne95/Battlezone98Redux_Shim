/*
 * Entry: 00414f6b
 * Name: GunTowerFriend::`scalar_deleting_destructor'
 * Namespace: GunTowerFriend
 * Signature: void * `scalar_deleting_destructor'(GunTowerFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GunTowerFriend::_scalar_deleting_destructor_(GunTowerFriend *this,uint param_1)

{
  GunTowerProcess::~GunTowerProcess((GunTowerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
