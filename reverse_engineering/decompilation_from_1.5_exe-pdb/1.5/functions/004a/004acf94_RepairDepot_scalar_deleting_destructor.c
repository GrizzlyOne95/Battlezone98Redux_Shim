/*
 * Entry: 004acf94
 * Name: RepairDepot::`scalar_deleting_destructor'
 * Namespace: RepairDepot
 * Signature: void * `scalar_deleting_destructor'(RepairDepot * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RepairDepot::_scalar_deleting_destructor_(RepairDepot *this,uint param_1)

{
  ~RepairDepot(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
