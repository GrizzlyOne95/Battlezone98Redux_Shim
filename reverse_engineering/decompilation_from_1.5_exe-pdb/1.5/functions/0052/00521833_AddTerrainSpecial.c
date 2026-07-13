/*
 * Entry: 00521833
 * Name: AddTerrainSpecial
 * Namespace: Global
 * Signature: void AddTerrainSpecial(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddTerrainSpecial(_OBJ76 *param_1)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  VECTOR_3D local_10;
  
  if ((param_1->class_id != CLASS_ID_PARKING_LOT) && (param_1->class_id != CLASS_ID_SCROUNGE)) {
    pVVar1 = get_obj_geometric_center(&local_10,param_1);
    (param_1->bSphere).origin.x = pVVar1->x;
    (param_1->bSphere).origin.y = pVVar1->y;
    (param_1->bSphere).origin.z = pVVar1->z;
    fVar2 = get_obj_radius(param_1,*pVVar1);
    (param_1->bSphere).radius = fVar2;
  }
  if (TerrainSpecialList == (_OBJ76 *)0x0) {
    TerrainSpecialList = param_1;
  }
  else {
    param_1->sibling = TerrainSpecialList->sibling;
    TerrainSpecialList->sibling = param_1;
  }
  return;
}
