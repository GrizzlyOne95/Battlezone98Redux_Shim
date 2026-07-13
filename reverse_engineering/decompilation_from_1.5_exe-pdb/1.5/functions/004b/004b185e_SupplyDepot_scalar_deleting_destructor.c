/*
 * Entry: 004b185e
 * Name: SupplyDepot::`scalar_deleting_destructor'
 * Namespace: SupplyDepot
 * Signature: void * `scalar_deleting_destructor'(SupplyDepot * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SupplyDepot::_scalar_deleting_destructor_(SupplyDepot *this,uint param_1)

{
  ~SupplyDepot(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
