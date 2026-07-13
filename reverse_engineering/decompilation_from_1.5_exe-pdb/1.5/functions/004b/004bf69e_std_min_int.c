/*
 * Entry: 004bf69e
 * Name: std::min<int>
 * Namespace: std
 * Signature: int * min<int>(int * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int * __cdecl std::min<int>(int *param_1,int *param_2)

{
  if (*param_1 <= *param_2) {
    param_2 = param_1;
  }
  return param_2;
}
