/*
 * Entry: 00514fca
 * Name: NR_Free_Convert_Matrix
 * Namespace: Global
 * Signature: void NR_Free_Convert_Matrix(float * * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Convert_Matrix(float **param_1,int param_2,int param_3,int param_4,int param_5)

{
  free(param_1 + param_2);
  return;
}
