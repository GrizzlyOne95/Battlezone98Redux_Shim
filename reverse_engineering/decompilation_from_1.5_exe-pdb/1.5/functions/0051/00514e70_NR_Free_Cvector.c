/*
 * Entry: 00514e70
 * Name: NR_Free_Cvector
 * Namespace: Global
 * Signature: void NR_Free_Cvector(uchar * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Cvector(uchar *param_1,int param_2,int param_3)

{
  free(param_1 + param_2);
  return;
}
