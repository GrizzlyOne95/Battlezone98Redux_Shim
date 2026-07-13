/*
 * Entry: 004901cc
 * Name: DistributedObject_ReadPermState
 * Namespace: Global
 * Signature: void DistributedObject_ReadPermState(ushort param_1, uint param_2, ushort param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
DistributedObject_ReadPermState(ushort param_1,uint param_2,ushort param_3,void *param_4)

{
  if (((0x1ff < param_3) && ((uint)param_3 < DistributedObject::dwGlobalIDCounter + 0x200)) ||
     ((ushort)(param_3 - 0x400) < 0x200)) {
    DistributedObject::ReadPermState(param_1,param_2,param_3,param_4);
  }
  return;
}
