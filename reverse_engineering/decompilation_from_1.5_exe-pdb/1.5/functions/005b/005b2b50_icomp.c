/*
 * Entry: 005b2b50
 * Name: icomp
 * Namespace: Global
 * Signature: int icomp(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl icomp(void *param_1,void *param_2)

{
  return **(int **)param_1 - **(int **)param_2;
}
