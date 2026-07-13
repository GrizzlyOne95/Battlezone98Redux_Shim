/*
 * Entry: 00553175
 * Name: SimpleVehicleList::`scalar_deleting_destructor'
 * Namespace: SimpleVehicleList
 * Signature: void * `scalar_deleting_destructor'(SimpleVehicleList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SimpleVehicleList::_scalar_deleting_destructor_(SimpleVehicleList *this,uint param_1)

{
  ~SimpleVehicleList(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
