/*
 * Entry: 005a7980
 * Name: vorbis_book_codelen
 * Namespace: Global
 * Signature: long vorbis_book_codelen(codebook * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl vorbis_book_codelen(codebook *param_1,int param_2)

{
  if (param_1->c != (static_codebook *)0x0) {
    return (int)*(char *)((int)param_1->c->lengthlist + param_2);
  }
  return -1;
}
