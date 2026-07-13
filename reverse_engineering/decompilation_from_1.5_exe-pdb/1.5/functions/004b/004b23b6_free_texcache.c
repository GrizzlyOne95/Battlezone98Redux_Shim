/*
 * Entry: 004b23b6
 * Name: free_texcache
 * Namespace: Global
 * Signature: int free_texcache(_texcache * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_texcache(_texcache *param_1)

{
  free(param_1);
  return 1;
}
