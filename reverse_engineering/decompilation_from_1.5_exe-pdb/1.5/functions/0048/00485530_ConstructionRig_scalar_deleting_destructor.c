/*
 * Entry: 00485530
 * Name: ConstructionRig::`scalar_deleting_destructor'
 * Namespace: ConstructionRig
 * Signature: void * `scalar_deleting_destructor'(ConstructionRig * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ConstructionRig::_scalar_deleting_destructor_(ConstructionRig *this,uint param_1)

{
  ~ConstructionRig(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
