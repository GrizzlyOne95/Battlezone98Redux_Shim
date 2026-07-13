/*
 * Entry: 0055234a
 * Name: MapList::VehicleGetAvi
 * Namespace: MapList
 * Signature: char * VehicleGetAvi(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::VehicleGetAvi(MapList *this)

{
  char *pcVar1;
  
  if (this->vehicleList != (VehicleList *)0x0) {
    pcVar1 = VehicleList::GetAvi(this->vehicleList);
    return pcVar1;
  }
  return "";
}
