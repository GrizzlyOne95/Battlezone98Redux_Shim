/*
 * Entry: 00514ee7
 * Name: NR_Free_Ptr_Matrix
 * Namespace: Global
 * Signature: void NR_Free_Ptr_Matrix(void * * * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Ptr_Matrix(void ***param_1,int param_2,int param_3,int param_4,int param_5)

{
  free(param_1 + param_2);
  return;
}
