/*
 * Entry: 00514e5c
 * Name: NR_Free_Vector
 * Namespace: Global
 * Signature: void NR_Free_Vector(float * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Vector(float *param_1,int param_2,int param_3)

{
  free(param_1 + param_2);
  return;
}
