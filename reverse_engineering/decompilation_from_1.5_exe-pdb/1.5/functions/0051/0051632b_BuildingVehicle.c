/*
 * Entry: 0051632b
 * Name: BuildingVehicle
 * Namespace: Global
 * Signature: bool BuildingVehicle(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl BuildingVehicle(ulong param_1)

{
  if (((param_1 != 0x41524d52) && (param_1 != 0x46414354)) && (param_1 != 0x52435943)) {
    return false;
  }
  return true;
}
