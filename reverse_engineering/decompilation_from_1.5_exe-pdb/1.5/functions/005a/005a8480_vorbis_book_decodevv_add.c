/*
 * Entry: 005a8480
 * Name: vorbis_book_decodevv_add
 * Namespace: Global
 * Signature: long vorbis_book_decodevv_add(codebook * param_1, float * * param_2, long param_3, int param_4, oggpack_buffer * param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
vorbis_book_decodevv_add
          (codebook *param_1,float **param_2,long param_3,int param_4,oggpack_buffer *param_5,
          int param_6)

{
  float **ppfVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  if (0 < param_1->used_entries) {
    iVar4 = param_3 / param_4;
    while (iVar4 < (param_6 + param_3) / param_4) {
      lVar5 = decode_packed_entry_number(param_1,param_5);
      if (lVar5 == -1) {
        return -1;
      }
      iVar2 = param_1->dim;
      pfVar3 = param_1->valuelist;
      iVar6 = 0;
      if (0 < iVar2) {
        do {
          ppfVar1 = param_2 + iVar7;
          iVar7 = iVar7 + 1;
          (*ppfVar1)[iVar4] = pfVar3[iVar2 * lVar5 + iVar6] + (*ppfVar1)[iVar4];
          if (iVar7 == param_4) {
            iVar7 = 0;
            iVar4 = iVar4 + 1;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < param_1->dim);
      }
    }
  }
  return 0;
}
