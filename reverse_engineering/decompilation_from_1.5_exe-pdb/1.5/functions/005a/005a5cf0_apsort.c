/*
 * Entry: 005a5cf0
 * Name: apsort
 * Namespace: Global
 * Signature: int apsort(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl apsort(void *param_1,void *param_2)

{
  uint uVar1;
  
  uVar1 = (uint)(**(float **)param_1 < **(float **)param_2);
  if (**(float **)param_2 < **(float **)param_1) {
    return uVar1 - 1;
  }
  return uVar1;
}
