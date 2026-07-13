/*
 * Entry: 00514eab
 * Name: NR_Free_Dvector
 * Namespace: Global
 * Signature: void NR_Free_Dvector(double * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NR_Free_Dvector(double *param_1,int param_2,int param_3)

{
  free(param_1 + param_2);
  return;
}
