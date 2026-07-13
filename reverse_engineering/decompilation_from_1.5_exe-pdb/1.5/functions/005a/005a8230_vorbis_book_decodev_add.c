/*
 * Entry: 005a8230
 * Name: vorbis_book_decodev_add
 * Namespace: Global
 * Signature: long vorbis_book_decodev_add(codebook * param_1, float * param_2, oggpack_buffer * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
vorbis_book_decodev_add(codebook *param_1,float *param_2,oggpack_buffer *param_3,int param_4)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (0 < param_1->used_entries) {
    iVar7 = 0;
    if (param_1->dim < 9) {
      if (0 < param_4) {
        do {
          lVar4 = decode_packed_entry_number(param_1,param_3);
          if (lVar4 == -1) {
            return -1;
          }
          pfVar2 = param_1->valuelist + param_1->dim * lVar4;
          iVar6 = 0;
          iVar8 = iVar7;
          switch(param_1->dim) {
          case 8:
            iVar6 = 1;
            iVar8 = iVar7 + 1;
            param_2[iVar7] = *pfVar2 + param_2[iVar7];
          case 7:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar7 = iVar8 + 1;
            param_2[iVar8] = *pfVar1 + param_2[iVar8];
          case 6:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar8 = iVar7 + 1;
            param_2[iVar7] = *pfVar1 + param_2[iVar7];
          case 5:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar7 = iVar8 + 1;
            param_2[iVar8] = *pfVar1 + param_2[iVar8];
          case 4:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar8 = iVar7 + 1;
            param_2[iVar7] = *pfVar1 + param_2[iVar7];
          case 3:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar7 = iVar8 + 1;
            param_2[iVar8] = *pfVar1 + param_2[iVar8];
          case 2:
            pfVar1 = pfVar2 + iVar6;
            iVar6 = iVar6 + 1;
            iVar8 = iVar7 + 1;
            param_2[iVar7] = *pfVar1 + param_2[iVar7];
          case 1:
            iVar7 = iVar8 + 1;
            param_2[iVar8] = pfVar2[iVar6] + param_2[iVar8];
          }
        } while (iVar7 < param_4);
      }
    }
    else if (0 < param_4) {
      do {
        lVar4 = decode_packed_entry_number(param_1,param_3);
        if (lVar4 == -1) {
          return -1;
        }
        iVar8 = param_1->dim;
        pfVar2 = param_1->valuelist;
        iVar5 = 0;
        iVar6 = iVar7;
        if (0 < iVar8) {
          do {
            iVar3 = iVar8 * lVar4 + iVar5;
            iVar5 = iVar5 + 1;
            iVar7 = iVar6 + 1;
            param_2[iVar6] = pfVar2[iVar3] + param_2[iVar6];
            iVar6 = iVar7;
          } while (iVar5 < param_1->dim);
        }
      } while (iVar7 < param_4);
      return 0;
    }
  }
  return 0;
}
