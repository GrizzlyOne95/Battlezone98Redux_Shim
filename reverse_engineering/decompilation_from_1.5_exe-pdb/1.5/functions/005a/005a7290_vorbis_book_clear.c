/*
 * Entry: 005a7290
 * Name: vorbis_book_clear
 * Namespace: Global
 * Signature: void vorbis_book_clear(codebook * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_book_clear(codebook *param_1)

{
  if (param_1->valuelist != (float *)0x0) {
    free(param_1->valuelist);
  }
  if (param_1->codelist != (uint *)0x0) {
    free(param_1->codelist);
  }
  if (param_1->dec_index != (int *)0x0) {
    free(param_1->dec_index);
  }
  if (param_1->dec_codelengths != (char *)0x0) {
    free(param_1->dec_codelengths);
  }
  if (param_1->dec_firsttable != (uint *)0x0) {
    free(param_1->dec_firsttable);
  }
  memset(param_1,0,0x38);
  return;
}
