/*
 * Entry: 005a8380
 * Name: vorbis_book_decodev_set
 * Namespace: Global
 * Signature: long vorbis_book_decodev_set(codebook * param_1, float * param_2, oggpack_buffer * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
vorbis_book_decodev_set(codebook *param_1,float *param_2,oggpack_buffer *param_3,int param_4)

{
  float *pfVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  
  if (param_1->used_entries < 1) {
    if (0 < param_4) {
      for (; param_4 != 0; param_4 = param_4 + -1) {
        *param_2 = 0.0;
        param_2 = param_2 + 1;
      }
    }
  }
  else {
    iVar6 = 0;
    if (0 < param_4) {
      while( true ) {
        lVar2 = decode_packed_entry_number(param_1,param_3);
        if (lVar2 == -1) {
          return -1;
        }
        pfVar1 = param_1->valuelist;
        iVar4 = param_1->dim * lVar2;
        iVar3 = 0;
        if (param_4 <= iVar6) break;
        if (3 < param_4 - iVar6) {
          pfVar5 = param_2 + iVar6 + 2;
          do {
            if (param_1->dim <= iVar3) goto LAB_005a8446;
            pfVar5[-2] = pfVar1[iVar4 + iVar3];
            if (param_1->dim <= iVar3 + 1) {
              iVar6 = iVar6 + 1;
              goto LAB_005a8446;
            }
            pfVar5[-1] = pfVar1[iVar4 + iVar3 + 1];
            if (param_1->dim <= iVar3 + 2) {
              iVar6 = iVar6 + 2;
              goto LAB_005a8446;
            }
            *pfVar5 = pfVar1[iVar4 + iVar3 + 2];
            if (param_1->dim <= iVar3 + 3) {
              iVar6 = iVar6 + 3;
              goto LAB_005a8446;
            }
            iVar6 = iVar6 + 4;
            pfVar5[1] = pfVar1[iVar4 + iVar3 + 3];
            iVar3 = iVar3 + 4;
            pfVar5 = pfVar5 + 4;
          } while (iVar6 < param_4 + -3);
        }
        if (param_4 <= iVar6) {
          return 0;
        }
        while (iVar3 < param_1->dim) {
          param_2[iVar6] = pfVar1[iVar4 + iVar3];
          iVar6 = iVar6 + 1;
          iVar3 = iVar3 + 1;
          if (param_4 <= iVar6) {
            return 0;
          }
        }
LAB_005a8446:
        if (param_4 <= iVar6) {
          return 0;
        }
      }
    }
  }
  return 0;
}
