/*
 * Entry: 0053a75d
 * Name: SprayBuilding::`scalar_deleting_destructor'
 * Namespace: SprayBuilding
 * Signature: void * `scalar_deleting_destructor'(SprayBuilding * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SprayBuilding::_scalar_deleting_destructor_(SprayBuilding *this,uint param_1)

{
  ~SprayBuilding(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
