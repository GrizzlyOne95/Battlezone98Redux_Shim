/*
 * Entry: 00556b82
 * Name: MapList::VehicleSelectionDown
 * Namespace: MapList
 * Signature: void VehicleSelectionDown(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::VehicleSelectionDown(MapList *this)

{
  if (this->vehicleList != (VehicleList *)0x0) {
    VehicleList::SelectionDown(this->vehicleList);
  }
  StartAnim(this);
  return;
}
