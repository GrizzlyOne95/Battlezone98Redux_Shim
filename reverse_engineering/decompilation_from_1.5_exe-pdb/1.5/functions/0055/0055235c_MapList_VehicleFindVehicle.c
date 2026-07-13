/*
 * Entry: 0055235c
 * Name: MapList::VehicleFindVehicle
 * Namespace: MapList
 * Signature: char * VehicleFindVehicle(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall MapList::VehicleFindVehicle(MapList *this,char *param_1)

{
  char *pcVar1;
  
  if (this->vehicleList != (VehicleList *)0x0) {
    pcVar1 = VehicleList::FindVehicle(this->vehicleList,param_1);
    return pcVar1;
  }
  return (char *)0x0;
}
