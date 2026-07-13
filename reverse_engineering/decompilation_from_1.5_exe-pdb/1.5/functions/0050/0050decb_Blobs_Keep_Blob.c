/*
 * Entry: 0050decb
 * Name: Blobs_Keep_Blob
 * Namespace: Global
 * Signature: int Blobs_Keep_Blob(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Blobs_Keep_Blob(int param_1)

{
  if (((((0x31 < blob_array[param_1].area) && (blob_array[param_1].area < 0x97)) &&
       (0.55 <= blob_array[param_1].aspect)) &&
      ((blob_array[param_1].aspect <= 1.7 && (0.65 <= blob_array[param_1].fill_percent)))) &&
     ((blob_array[param_1].fill_percent <= 1.001 &&
      ((blob_array[param_1].max_r - blob_array[param_1].min_r < 0x15 &&
       (blob_array[param_1].max_c - blob_array[param_1].min_c < 0x15)))))) {
    return 1;
  }
  return 0;
}
