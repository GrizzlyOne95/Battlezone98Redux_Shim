/*
 * Entry: 0051634a
 * Name: IsBuilding
 * Namespace: Global
 * Signature: bool IsBuilding(GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsBuilding(GameObjectClass *param_1)

{
  bool bVar1;
  
  if (param_1->class_id == CLASS_ID_STRUCTURE1) {
    return -1 < param_1->categoryMin;
  }
  if (param_1->sig == 0x54555252) {
    return true;
  }
  bVar1 = BuildingVehicle(param_1->sig);
  return bVar1;
}
