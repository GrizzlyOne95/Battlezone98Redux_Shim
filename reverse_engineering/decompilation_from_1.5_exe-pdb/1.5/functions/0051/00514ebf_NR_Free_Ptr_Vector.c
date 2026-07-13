/*
 * Entry: 00514ebf
 * Name: NR_Free_Ptr_Vector
 * Namespace: Global
 * Signature: void NR_Free_Ptr_Vector(void * * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Ptr_Vector(void **param_1,int param_2,int param_3)

{
  free(param_1 + param_2);
  return;
}
