/*
 * Entry: 005a80d0
 * Name: vorbis_book_decodevs_add
 * Namespace: Global
 * Signature: long vorbis_book_decodevs_add(codebook * param_1, float * param_2, oggpack_buffer * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

long __cdecl
vorbis_book_decodevs_add(codebook *param_1,float *param_2,oggpack_buffer *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  float *pfVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 auStack_30 [3];
  float *local_10;
  int local_c;
  int local_8;
  
  if (0 < param_1->used_entries) {
    iVar3 = param_4 / param_1->dim;
    auStack_30[2] = 0x5a80ff;
    piVar6 = (int *)(&stack0xffffffdc + iVar3 * -8);
    auStack_30[2 - iVar3] = 0x5a8109;
    local_8 = 0;
    if (0 < iVar3) {
      do {
        auStack_30[iVar3 * -2 + 2] = param_3;
        auStack_30[iVar3 * -2 + 1] = param_1;
        auStack_30[iVar3 * -2] = 0x5a812b;
        lVar4 = decode_packed_entry_number
                          ((codebook *)auStack_30[iVar3 * -2 + 1],
                           (oggpack_buffer *)auStack_30[iVar3 * -2 + 2]);
        piVar6[iVar3] = lVar4;
        if (lVar4 == -1) {
          return -1;
        }
        local_8 = local_8 + 1;
        *piVar6 = (int)(param_1->valuelist + param_1->dim * lVar4);
        piVar6 = piVar6 + 1;
      } while (local_8 < iVar3);
    }
    iVar7 = 0;
    local_8 = 0;
    local_c = 0;
    if (0 < param_1->dim) {
      local_10 = param_2;
      do {
        iVar8 = 0;
        if (3 < iVar3) {
          iVar9 = (iVar3 - 4U >> 2) + 1;
          iVar8 = iVar9 * 4;
          pfVar5 = local_10;
          piVar6 = (int *)(&stack0xffffffe4 + iVar3 * -8);
          do {
            iVar1 = piVar6[-1];
            iVar9 = iVar9 + -1;
            *pfVar5 = *(float *)(piVar6[-2] + iVar7) + *pfVar5;
            iVar2 = *piVar6;
            pfVar5[1] = *(float *)(iVar1 + iVar7) + pfVar5[1];
            iVar1 = piVar6[1];
            pfVar5[2] = *(float *)(iVar7 + iVar2) + pfVar5[2];
            pfVar5[3] = *(float *)(iVar1 + iVar7) + pfVar5[3];
            pfVar5 = pfVar5 + 4;
            piVar6 = piVar6 + 4;
          } while (iVar9 != 0);
        }
        if (iVar8 < iVar3) {
          pfVar5 = param_2 + iVar8 + local_c;
          do {
            iVar9 = iVar8 * 4;
            iVar8 = iVar8 + 1;
            *pfVar5 = *(float *)(*(int *)(&stack0xffffffdc + iVar9 + iVar3 * -8) + iVar7) + *pfVar5;
            pfVar5 = pfVar5 + 1;
          } while (iVar8 < iVar3);
        }
        local_c = local_c + iVar3;
        local_8 = local_8 + 1;
        local_10 = local_10 + iVar3;
        iVar7 = iVar7 + 4;
      } while (local_8 < param_1->dim);
    }
  }
  return 0;
}
