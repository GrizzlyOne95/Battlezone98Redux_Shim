/*
 * Entry: 005a7450
 * Name: sort32a
 * Namespace: Global
 * Signature: int sort32a(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sort32a(void *param_1,void *param_2)

{
  return (uint)(**(uint **)param_2 < **(uint **)param_1) -
         (uint)(**(uint **)param_1 < **(uint **)param_2);
}
