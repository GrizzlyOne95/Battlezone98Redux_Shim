/*
 * Entry: 0049b1e5
 * Name: Geom_Delete
 * Namespace: Global
 * Signature: void Geom_Delete(_GEOMETRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Geom_Delete(_GEOMETRY *param_1)

{
  int *piVar1;
  
  piVar1 = &param_1->cache_info->refCount;
  *piVar1 = *piVar1 + -1;
  return;
}
