/*
 * Entry: 005a72f0
 * Name: vorbis_book_init_encode
 * Namespace: Global
 * Signature: int vorbis_book_init_encode(codebook * param_1, static_codebook * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_book_init_encode(codebook *param_1,static_codebook *param_2)

{
  uint uVar1;
  uint *puVar2;
  long lVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  double dVar4;
  
  memset(param_1,0,0x38);
  param_1->c = param_2;
  param_1->entries = param_2->entries;
  param_1->used_entries = param_2->entries;
  param_1->dim = param_2->dim;
  puVar2 = _make_words((char *)param_2->lengthlist,param_2->entries,0);
  param_1->codelist = puVar2;
  lVar3 = _book_maptype1_quantvals(param_2);
  param_1->quantvals = lVar3;
  uVar1 = param_2->q_min;
  dVar4 = (double)(uVar1 & 0x1fffff);
  if ((int)uVar1 < 0) {
    dVar4 = -dVar4;
  }
  dVar4 = ldexp(dVar4,((int)uVar1 >> 0x15 & 0x3ffU) - 0x314);
  floor((double)((float)dVar4 + 0.5));
  _ftol2_sse();
  param_1->minval = extraout_EAX;
  uVar1 = param_2->q_delta;
  dVar4 = (double)(uVar1 & 0x1fffff);
  if ((int)uVar1 < 0) {
    dVar4 = -dVar4;
  }
  dVar4 = ldexp(dVar4,((int)uVar1 >> 0x15 & 0x3ffU) - 0x314);
  floor((double)((float)dVar4 + 0.5));
  _ftol2_sse();
  param_1->delta = extraout_EAX_00;
  return 0;
}
