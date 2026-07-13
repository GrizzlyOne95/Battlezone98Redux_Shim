/*
 * Entry: 0054fab2
 * Name: free_line
 * Namespace: Global
 * Signature: int free_line(SCROLL_LINE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl free_line(SCROLL_LINE *param_1)

{
  free(param_1);
  return 1;
}
