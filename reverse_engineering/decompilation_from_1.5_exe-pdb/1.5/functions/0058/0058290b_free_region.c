/*
 * Entry: 0058290b
 * Name: free_region
 * Namespace: Global
 * Signature: int free_region(INPUT_REGION * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_region(INPUT_REGION *param_1)

{
  free(param_1);
  return 1;
}
