/*
 * Entry: 00552338
 * Name: MapList::VehicleGetName
 * Namespace: MapList
 * Signature: char * VehicleGetName(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::VehicleGetName(MapList *this)

{
  char *pcVar1;
  
  if (this->vehicleList != (VehicleList *)0x0) {
    pcVar1 = VehicleList::GetName(this->vehicleList);
    return pcVar1;
  }
  return "";
}
