/*
 * Entry: 005a7960
 * Name: vorbis_book_codeword
 * Namespace: Global
 * Signature: long vorbis_book_codeword(codebook * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl vorbis_book_codeword(codebook *param_1,int param_2)

{
  if (param_1->c != (static_codebook *)0x0) {
    return param_1->codelist[param_2];
  }
  return -1;
}
