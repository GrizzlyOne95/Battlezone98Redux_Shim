/*
 * Entry: 0049018c
 * Name: DistributedObject_ReceiveTempState
 * Namespace: Global
 * Signature: void DistributedObject_ReceiveTempState(ushort param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject_ReceiveTempState(ushort param_1,char *param_2,uint param_3)

{
  DistributedObject::ReceiveTempState(param_1,param_2 + 4,param_3 - 4,*(float *)param_2);
  return;
}
