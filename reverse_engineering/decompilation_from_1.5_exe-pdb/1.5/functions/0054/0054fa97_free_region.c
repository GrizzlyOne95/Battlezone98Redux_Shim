/*
 * Entry: 0054fa97
 * Name: free_region
 * Namespace: Global
 * Signature: int free_region(SCROLL_REGION * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_region(SCROLL_REGION *param_1)

{
  free(param_1);
  return 1;
}
