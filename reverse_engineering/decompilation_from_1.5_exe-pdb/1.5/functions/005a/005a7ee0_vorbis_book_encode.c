/*
 * Entry: 005a7ee0
 * Name: vorbis_book_encode
 * Namespace: Global
 * Signature: int vorbis_book_encode(codebook * param_1, int param_2, oggpack_buffer * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_book_encode(codebook *param_1,int param_2,oggpack_buffer *param_3)

{
  if (-1 < param_2) {
    if (param_2 < param_1->c->entries) {
      oggpack_write(param_3,param_1->codelist[param_2],
                    (int)*(char *)((int)param_1->c->lengthlist + param_2));
      return (int)*(char *)((int)param_1->c->lengthlist + param_2);
    }
  }
  return 0;
}
