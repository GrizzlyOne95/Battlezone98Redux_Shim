/*
 * Entry: 0047bfbf
 * Name: AnimBuilding::`scalar_deleting_destructor'
 * Namespace: AnimBuilding
 * Signature: void * `scalar_deleting_destructor'(AnimBuilding * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AnimBuilding::_scalar_deleting_destructor_(AnimBuilding *this,uint param_1)

{
  ~AnimBuilding(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
