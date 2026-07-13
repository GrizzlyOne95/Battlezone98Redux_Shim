/*
 * Entry: 0048aff7
 * Name: DistributedObject_SetGlobalPlayerID
 * Namespace: Global
 * Signature: void DistributedObject_SetGlobalPlayerID(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject_SetGlobalPlayerID(ushort param_1)

{
  DistributedObject::global_activnet_id = param_1;
  return;
}
