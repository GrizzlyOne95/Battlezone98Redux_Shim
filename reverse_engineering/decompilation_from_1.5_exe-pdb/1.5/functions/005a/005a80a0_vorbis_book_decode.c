/*
 * Entry: 005a80a0
 * Name: vorbis_book_decode
 * Namespace: Global
 * Signature: long vorbis_book_decode(codebook * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl vorbis_book_decode(codebook *param_1,oggpack_buffer *param_2)

{
  long lVar1;
  
  if (0 < param_1->used_entries) {
    lVar1 = decode_packed_entry_number(param_1,param_2);
    if (-1 < lVar1) {
      return param_1->dec_index[lVar1];
    }
  }
  return -1;
}
