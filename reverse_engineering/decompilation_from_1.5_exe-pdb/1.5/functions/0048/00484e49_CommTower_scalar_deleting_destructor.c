/*
 * Entry: 00484e49
 * Name: CommTower::`scalar_deleting_destructor'
 * Namespace: CommTower
 * Signature: void * `scalar_deleting_destructor'(CommTower * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CommTower::_scalar_deleting_destructor_(CommTower *this,uint param_1)

{
  ~CommTower(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
