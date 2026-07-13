/*
 * Entry: 0050dd7c
 * Name: Blobs_Single_Band_Delete
 * Namespace: Global
 * Signature: void Blobs_Single_Band_Delete(ushort * * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Single_Band_Delete(ushort **param_1,int param_2,int param_3)

{
  NR_Free_Smatrix(param_1,0,param_2 + -1,0,param_3 + -1);
  return;
}
