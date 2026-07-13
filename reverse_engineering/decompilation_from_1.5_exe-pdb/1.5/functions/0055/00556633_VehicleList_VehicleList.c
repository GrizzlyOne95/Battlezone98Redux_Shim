/*
 * Entry: 00556633
 * Name: VehicleList::VehicleList
 * Namespace: VehicleList
 * Signature: VehicleList * VehicleList(VehicleList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VehicleList * __thiscall VehicleList::VehicleList(VehicleList *this)

{
  this->vehicleNameLabel = (TextLabel *)0x0;
  this->vehicleDesc = (TextWindow *)0x0;
  this->currentSelection = 0;
  SetCurrentSelection(this);
  this->s = (_s *)0x0;
  this->count = 0;
  this->validVehicles = (char *)0x0;
  validVehicles = (char *)0x0;
  return this;
}
