/*
 * Entry: 0055712f
 * Name: VehicleList::`scalar_deleting_destructor'
 * Namespace: VehicleList
 * Signature: void * `scalar_deleting_destructor'(VehicleList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall VehicleList::_scalar_deleting_destructor_(VehicleList *this,uint param_1)

{
  Init(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
