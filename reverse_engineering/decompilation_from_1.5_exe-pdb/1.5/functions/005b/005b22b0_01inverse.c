/*
 * Entry: 005b22b0
 * Name: _01inverse
 * Namespace: Global
 * Signature: int _01inverse(vorbis_block * param_1, void * param_2, float * * param_3, int param_4, _func___cdecl_long_codebook_ptr_float_ptr_oggpack_buffer_ptr_int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl
_01inverse(vorbis_block *param_1,void *param_2,float **param_3,int param_4,
          _func___cdecl_long_codebook_ptr_float_ptr_oggpack_buffer_ptr_int *param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  void *pvVar8;
  long lVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int aiStack_50 [4];
  undefined4 uStack_40;
  int local_2c;
  undefined1 *local_28;
  int local_24;
  int local_1c;
  int local_14;
  int local_c;
  int local_8;
  
  piVar1 = *(int **)param_2;
  iVar2 = **(int **)((int)param_2 + 0x10);
  iVar3 = piVar1[2];
  iVar6 = param_1->pcmend >> 1;
  if (piVar1[1] < iVar6) {
    iVar6 = piVar1[1];
  }
  if (0 < iVar6 - *piVar1) {
    iVar7 = (iVar6 - *piVar1) / iVar3;
    uStack_40 = 0x5b2305;
    iVar6 = param_4 * -4;
    iVar11 = 0;
    if (0 < param_4) {
      do {
        aiStack_50[4 - param_4] = ((iVar7 + -1 + iVar2) / iVar2) * 4;
        aiStack_50[3 - param_4] = (int)param_1;
        aiStack_50[2 - param_4] = 0x5b231f;
        pvVar8 = _vorbis_block_alloc((vorbis_block *)aiStack_50[3 - param_4],aiStack_50[4 - param_4]
                                    );
        *(void **)(&stack0xffffffc4 + iVar11 * 4 + iVar6) = pvVar8;
        iVar11 = iVar11 + 1;
      } while (iVar11 < param_4);
    }
    local_c = 0;
    if (0 < *(int *)((int)param_2 + 8)) {
      do {
        local_28 = &stack0xffffffc4 + iVar6;
        iVar11 = 0;
        local_2c = 0;
        if (0 < iVar7) {
          local_8 = 0;
          do {
            if ((local_c == 0) && (iVar12 = 0, 0 < param_4)) {
              do {
                uVar4 = *(undefined4 *)((int)param_2 + 0x10);
                aiStack_50[4 - param_4] = (int)&param_1->opb;
                aiStack_50[3 - param_4] = uVar4;
                aiStack_50[2 - param_4] = 0x5b236b;
                lVar9 = vorbis_book_decode((codebook *)aiStack_50[3 - param_4],
                                           (oggpack_buffer *)aiStack_50[4 - param_4]);
                if (lVar9 == -1) {
                  return 0;
                }
                if (piVar1[4] <= lVar9) {
                  return 0;
                }
                iVar5 = *(int *)(*(int *)((int)param_2 + 0x1c) + lVar9 * 4);
                *(int *)(local_8 + *(int *)(&stack0xffffffc4 + iVar12 * 4 + iVar6)) = iVar5;
                if (iVar5 == 0) {
                  return 0;
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < param_4);
            }
            local_14 = 0;
            if (0 < iVar2) {
              local_1c = iVar11 * iVar3;
              do {
                piVar10 = (int *)(&stack0xffffffc4 + iVar6);
                if (iVar7 <= iVar11) break;
                local_24 = 0;
                if (0 < param_4) {
                  do {
                    iVar11 = *piVar1;
                    iVar12 = *(int *)(*(int *)(local_8 + *piVar10) + local_14 * 4);
                    if (((piVar1[iVar12 + 6] & 1 << ((byte)local_c & 0x1f)) != 0) &&
                       (iVar12 = *(int *)(*(int *)(*(int *)((int)param_2 + 0x14) + iVar12 * 4) +
                                         local_c * 4), iVar12 != 0)) {
                      aiStack_50[4 - param_4] = iVar3;
                      aiStack_50[3 - param_4] = (int)&param_1->opb;
                      aiStack_50[2 - param_4] =
                           *(int *)(((int)param_3 - (int)local_28) + (int)piVar10) +
                           (iVar11 + local_1c) * 4;
                      aiStack_50[1 - param_4] = iVar12;
                      aiStack_50[-param_4] = 0x5b242c;
                      lVar9 = (*param_5)((codebook *)aiStack_50[1 - param_4],
                                         (float *)aiStack_50[2 - param_4],
                                         (oggpack_buffer *)aiStack_50[3 - param_4],
                                         aiStack_50[4 - param_4]);
                      if (lVar9 == -1) {
                        return 0;
                      }
                    }
                    local_24 = local_24 + 1;
                    piVar10 = piVar10 + 1;
                    iVar11 = local_2c;
                  } while (local_24 < param_4);
                }
                local_1c = local_1c + iVar3;
                local_14 = local_14 + 1;
                iVar11 = iVar11 + 1;
                local_2c = iVar11;
              } while (local_14 < iVar2);
            }
            local_8 = local_8 + 4;
          } while (iVar11 < iVar7);
        }
        local_c = local_c + 1;
      } while (local_c < *(int *)((int)param_2 + 8));
    }
  }
  return 0;
}
