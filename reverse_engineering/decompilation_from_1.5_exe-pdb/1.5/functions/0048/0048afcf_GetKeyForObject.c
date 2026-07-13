/*
 * Entry: 0048afcf
 * Name: GetKeyForObject
 * Namespace: Global
 * Signature: ulong GetKeyForObject(DistributedObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl GetKeyForObject(DistributedObject *param_1)

{
  int in_ECX;
  
  if (0xffff < *(uint *)(in_ECX + 100)) {
    return *(int *)(in_ECX + 0x134) + 0x400;
  }
  return *(uint *)(in_ECX + 100) + 0x200;
}
