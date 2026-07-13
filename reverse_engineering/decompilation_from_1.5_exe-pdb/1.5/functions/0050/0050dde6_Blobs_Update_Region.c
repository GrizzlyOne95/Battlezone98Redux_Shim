/*
 * Entry: 0050dde6
 * Name: Blobs_Update_Region
 * Namespace: Global
 * Signature: void Blobs_Update_Region(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Update_Region(int param_1,int param_2,int param_3)

{
  blob_array[param_3].area = blob_array[param_3].area + 1;
  if (param_2 < blob_array[param_3].min_c) {
    blob_array[param_3].min_c = param_2;
  }
  if (blob_array[param_3].max_c < param_2) {
    blob_array[param_3].max_c = param_2;
  }
  if (param_1 < blob_array[param_3].min_r) {
    blob_array[param_3].min_r = param_1;
  }
  if (blob_array[param_3].max_r < param_1) {
    blob_array[param_3].max_r = param_1;
  }
  blob_array[param_3].r_sum = blob_array[param_3].r_sum + param_1;
  blob_array[param_3].c_sum = blob_array[param_3].c_sum + param_2;
  return;
}
