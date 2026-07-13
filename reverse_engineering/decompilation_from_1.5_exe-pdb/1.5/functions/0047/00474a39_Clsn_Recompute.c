/*
 * Entry: 00474a39
 * Name: Clsn_Recompute
 * Namespace: Global
 * Signature: void Clsn_Recompute(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Clsn_Recompute(_OBJ76 *param_1)

{
  tagENTITY *ptVar1;
  
  ptVar1 = FindObjectEntity(param_1);
  if (ptVar1->cType == CLSN_TYPE_CHILDREN) {
    ClearObjCollision(ptVar1->obj76);
  }
  Floor_ClearEntity(ptVar1);
  SetObjBbox(param_1);
  InitCollisionType((tagENTITY *)param_1);
  Floor_InitEntity(ptVar1);
  return;
}
