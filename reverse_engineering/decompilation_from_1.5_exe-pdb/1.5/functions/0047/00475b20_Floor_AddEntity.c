/*
 * Entry: 00475b20
 * Name: Floor_AddEntity
 * Namespace: Global
 * Signature: void Floor_AddEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Floor_AddEntity(tagENTITY *param_1)

{
  int iVar1;
  
  iVar1 = OwnsFloor(param_1->obj76);
  if (iVar1 != 0) {
    iVar1 = Floor_InitEntity(param_1);
    if (iVar1 != 0) {
      FloorList = NewWrapper(FloorList,(wrap_struct *)0x0,param_1);
    }
  }
  return;
}
