/*
 * Entry: 005b52c0
 * Name: comp
 * Namespace: Global
 * Signature: int comp(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl comp(void *param_1,void *param_2)

{
  if (*(float *)param_2 < *(float *)param_1) {
    return (*(float *)param_1 < *(float *)param_2) - 1;
  }
  return (uint)(*(float *)param_1 < *(float *)param_2);
}
