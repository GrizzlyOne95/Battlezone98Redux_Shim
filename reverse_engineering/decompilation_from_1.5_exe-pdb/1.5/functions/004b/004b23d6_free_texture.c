/*
 * Entry: 004b23d6
 * Name: free_texture
 * Namespace: Global
 * Signature: int free_texture(TEXTURE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_texture(TEXTURE *param_1)

{
  free(param_1);
  return 1;
}
