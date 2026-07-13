/*
 * Entry: 00556b6b
 * Name: MapList::VehicleSelectionUp
 * Namespace: MapList
 * Signature: void VehicleSelectionUp(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::VehicleSelectionUp(MapList *this)

{
  if (this->vehicleList != (VehicleList *)0x0) {
    VehicleList::SelectionUp(this->vehicleList);
  }
  StartAnim(this);
  return;
}
