/*
 * Entry: 00475af3
 * Name: Floor_InitEntity
 * Namespace: Global
 * Signature: int Floor_InitEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Floor_InitEntity(tagENTITY *param_1)

{
  CollectObjFloor(param_1->obj76,param_1,&Identity_Matrix,
                  (uint)(param_1->obj76->class_id == CLASS_ID_BRIDGE));
  return (uint)(param_1->clsnDetails != (void *)0x0);
}
