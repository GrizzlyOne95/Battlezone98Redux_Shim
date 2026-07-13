/*
 * Entry: 0050e20b
 * Name: Blobs_Blank_Region
 * Namespace: Global
 * Signature: void Blobs_Blank_Region(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Blank_Region(int param_1)

{
  blob_array[param_1].max_c = -1;
  blob_array[param_1].max_r = -1;
  blob_array[param_1].area = 0;
  blob_array[param_1].min_c = 1000;
  blob_array[param_1].min_r = 1000;
  blob_array[param_1].r_sum = 0;
  blob_array[param_1].c_sum = 0;
  return;
}
