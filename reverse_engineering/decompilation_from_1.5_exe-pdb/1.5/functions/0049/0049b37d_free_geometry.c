/*
 * Entry: 0049b37d
 * Name: free_geometry
 * Namespace: Global
 * Signature: int free_geometry(_GEOMETRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_geometry(_GEOMETRY *param_1)

{
  operator_delete__(param_1);
  return 1;
}
