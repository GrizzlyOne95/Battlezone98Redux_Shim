/*
 * Entry: 0048afec
 * Name: DistributedObject_SetDP
 * Namespace: Global
 * Signature: void DistributedObject_SetDP(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject_SetDP(dp_s *param_1)

{
  DistributedObject::dp = param_1;
  return;
}
