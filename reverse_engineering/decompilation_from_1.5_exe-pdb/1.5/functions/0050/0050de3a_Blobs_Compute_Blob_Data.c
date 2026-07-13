/*
 * Entry: 0050de3a
 * Name: Blobs_Compute_Blob_Data
 * Namespace: Global
 * Signature: void Blobs_Compute_Blob_Data(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Compute_Blob_Data(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = blob_array[param_1].area;
  if (iVar1 != 0) {
    iVar4 = blob_array[param_1].max_r - blob_array[param_1].min_r;
    iVar5 = blob_array[param_1].max_c - blob_array[param_1].min_c;
    blob_array[param_1].aspect = ((float)iVar4 + 1.0) / ((float)iVar5 + 1.0);
    fVar3 = (float)iVar1;
    blob_array[param_1].centroid_r = (float)blob_array[param_1].r_sum / fVar3;
    blob_array[param_1].centroid_c = (float)blob_array[param_1].c_sum / fVar3;
    fVar2 = (float)((iVar5 + 1) * (iVar4 + 1));
    if (1.0 < fVar2) {
      blob_array[param_1].fill_percent = fVar3 / fVar2;
      return;
    }
  }
  return;
}
