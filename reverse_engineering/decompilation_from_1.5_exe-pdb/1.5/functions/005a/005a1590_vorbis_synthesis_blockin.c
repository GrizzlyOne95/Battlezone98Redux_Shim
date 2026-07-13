/*
 * Entry: 005a1590
 * Name: vorbis_synthesis_blockin
 * Namespace: Global
 * Signature: int vorbis_synthesis_blockin(vorbis_dsp_state * param_1, vorbis_block * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_blockin(vorbis_dsp_state *param_1,vorbis_block *param_2)

{
  long64 *plVar1;
  int *piVar2;
  vorbis_info *pvVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  float *pfVar7;
  uint uVar8;
  byte bVar9;
  int iVar10;
  long64 lVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  int iVar16;
  int iVar17;
  float *pfVar18;
  int iVar19;
  uint uVar20;
  byte bVar21;
  int iVar22;
  float *pfVar23;
  int iVar24;
  int iVar25;
  float *pfVar26;
  uint uVar27;
  int iVar28;
  int local_38;
  uint local_2c;
  float *local_18;
  uint local_14;
  float *local_10;
  float *local_8;
  
  pvVar3 = param_1->vi;
  piVar4 = pvVar3->codec_setup;
  pvVar5 = param_1->backend_state;
  iVar19 = piVar4[0x392];
  if (param_2 == (vorbis_block *)0x0) {
    return -0x83;
  }
  if ((param_1->pcm_returned < param_1->pcm_current) && (param_1->pcm_returned != -1)) {
    return -0x83;
  }
  param_1->lW = param_1->W;
  uVar6 = *(uint *)((int)&param_1->sequence + 4);
  param_1->W = param_2->W;
  uVar27 = (uint)param_1->sequence;
  param_1->nW = -1;
  if ((((uVar27 & uVar6) == 0xffffffff) || (uVar27 + 1 != (int)param_2->sequence)) ||
     (uVar6 + (0xfffffffe < uVar27) != *(int *)((int)&param_2->sequence + 4))) {
    *(undefined4 *)&param_1->granulepos = 0xffffffff;
    *(undefined4 *)((int)&param_1->granulepos + 4) = 0xffffffff;
    *(undefined4 *)((int)pvVar5 + 0x80) = 0xffffffff;
    *(undefined4 *)((int)pvVar5 + 0x84) = 0xffffffff;
  }
  *(int *)&param_1->sequence = (int)param_2->sequence;
  *(undefined4 *)((int)&param_1->sequence + 4) = *(undefined4 *)((int)&param_2->sequence + 4);
  bVar9 = (byte)iVar19;
  if (param_2->pcm != (float **)0x0) {
    bVar21 = bVar9 + 1;
    iVar12 = piVar4[param_1->W] >> (bVar21 & 0x1f);
    iVar25 = *piVar4 >> (bVar21 & 0x1f);
    uVar27 = piVar4[1] >> (bVar21 & 0x1f);
    uVar6 = param_2->glue_bits;
    plVar1 = &param_1->glue_bits;
    lVar11 = *plVar1;
    *(uint *)plVar1 = (int)*plVar1 + uVar6;
    piVar2 = (int *)((int)&param_1->glue_bits + 4);
    *piVar2 = *piVar2 + ((int)uVar6 >> 0x1f) + (uint)CARRY4((uint)lVar11,uVar6);
    uVar6 = param_2->time_bits;
    plVar1 = &param_1->time_bits;
    lVar11 = *plVar1;
    *(uint *)plVar1 = (int)*plVar1 + uVar6;
    piVar2 = (int *)((int)&param_1->time_bits + 4);
    *piVar2 = *piVar2 + ((int)uVar6 >> 0x1f) + (uint)CARRY4((uint)lVar11,uVar6);
    uVar6 = param_2->floor_bits;
    plVar1 = &param_1->floor_bits;
    lVar11 = *plVar1;
    *(uint *)plVar1 = (int)*plVar1 + uVar6;
    piVar2 = (int *)((int)&param_1->floor_bits + 4);
    *piVar2 = *piVar2 + ((int)uVar6 >> 0x1f) + (uint)CARRY4((uint)lVar11,uVar6);
    uVar6 = param_2->res_bits;
    plVar1 = &param_1->res_bits;
    lVar11 = *plVar1;
    *(uint *)plVar1 = (int)*plVar1 + uVar6;
    piVar2 = (int *)((int)&param_1->res_bits + 4);
    *piVar2 = *piVar2 + ((int)uVar6 >> 0x1f) + (uint)CARRY4((uint)lVar11,uVar6);
    if (param_1->centerW == 0) {
      local_14 = 0;
      local_2c = uVar27;
    }
    else {
      local_2c = 0;
      local_14 = uVar27;
    }
    local_38 = 0;
    if (0 < pvVar3->channels) {
      do {
        if (param_1->lW == 0) {
          if (param_1->W == 0) {
            pfVar13 = _vorbis_window_get(*(int *)((int)pvVar5 + 4) - iVar19);
            pfVar7 = param_1->pcm[local_38] + local_2c;
            pfVar23 = param_2->pcm[local_38];
            iVar24 = 0;
            if (3 < iVar25) {
              pfVar15 = pfVar7 + 1;
              iVar28 = iVar24;
              pfVar18 = pfVar13 + 2;
              pfVar26 = pfVar13 + iVar25 + -2;
              do {
                pfVar14 = (float *)(((int)pfVar13 - (int)pfVar7) + (int)pfVar15);
                iVar24 = iVar28 + 4;
                pfVar15[-1] = pfVar26[1] * pfVar15[-1] + pfVar23[iVar28] * pfVar18[-2];
                *pfVar15 = *pfVar26 * *pfVar15 +
                           *(float *)(((int)pfVar23 - (int)pfVar13) + (int)pfVar14) * *pfVar14;
                pfVar15[1] = pfVar26[-1] * pfVar15[1] +
                             *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
                pfVar15[2] = pfVar26[-2] * pfVar15[2] + pfVar23[iVar28 + 3] * pfVar18[1];
                pfVar15 = pfVar15 + 4;
                iVar28 = iVar24;
                pfVar18 = pfVar18 + 4;
                pfVar26 = pfVar26 + -4;
              } while (iVar24 < iVar25 + -3);
            }
            if (iVar24 < iVar25) {
              iVar28 = iVar25 - iVar24;
              pfVar15 = pfVar7 + iVar24;
              local_8 = pfVar13 + (iVar25 - iVar24) + -1;
              do {
                pfVar18 = (float *)((int)pfVar15 + ((int)pfVar13 - (int)pfVar7));
                iVar28 = iVar28 + -1;
                *pfVar15 = *pfVar15 * *local_8 +
                           *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
                pfVar15 = pfVar15 + 1;
                local_8 = local_8 + -1;
              } while (iVar28 != 0);
            }
          }
          else {
            pfVar13 = _vorbis_window_get(*(int *)((int)pvVar5 + 4) - iVar19);
            pfVar23 = param_2->pcm[local_38];
            pfVar7 = param_1->pcm[local_38] + local_2c;
            iVar28 = (int)uVar27 / 2 - iVar25 / 2;
            iVar24 = 0;
            if (3 < iVar25) {
              iVar16 = (int)pfVar23 + (iVar28 * 4 - (int)pfVar13);
              pfVar15 = pfVar7 + 1;
              iVar17 = iVar24;
              pfVar18 = pfVar13 + 2;
              pfVar26 = pfVar13 + iVar25 + -2;
              do {
                pfVar14 = (float *)(((int)pfVar13 - (int)pfVar7) + (int)pfVar15);
                iVar24 = iVar17 + 4;
                pfVar15[-1] = pfVar26[1] * pfVar15[-1] + pfVar23[iVar28 + iVar17] * pfVar18[-2];
                *pfVar15 = *pfVar26 * *pfVar15 + *(float *)(iVar16 + (int)pfVar14) * *pfVar14;
                pfVar15[1] = pfVar26[-1] * pfVar15[1] + *(float *)((int)pfVar18 + iVar16) * *pfVar18
                ;
                pfVar15[2] = pfVar26[-2] * pfVar15[2] + pfVar23[iVar28 + iVar17 + 3] * pfVar18[1];
                pfVar15 = pfVar15 + 4;
                iVar17 = iVar24;
                pfVar18 = pfVar18 + 4;
                pfVar26 = pfVar26 + -4;
              } while (iVar24 < iVar25 + -3);
            }
            if (iVar24 < iVar25) {
              iVar17 = iVar25 - iVar24;
              iVar16 = iVar25 - iVar24;
              pfVar15 = pfVar7 + iVar24;
              iVar24 = iVar24 + iVar16;
              local_10 = pfVar13 + iVar17 + -1;
              do {
                pfVar18 = (float *)(((int)pfVar13 - (int)pfVar7) + (int)pfVar15);
                iVar16 = iVar16 + -1;
                *pfVar15 = *pfVar15 * *local_10 +
                           *(float *)((int)pfVar18 + (int)pfVar23 + (iVar28 * 4 - (int)pfVar13)) *
                           *pfVar18;
                pfVar15 = pfVar15 + 1;
                local_10 = local_10 + -1;
              } while (iVar16 != 0);
            }
            iVar17 = (int)uVar27 / 2 + iVar25 / 2;
            if (iVar24 < iVar17) {
              if (3 < iVar17 - iVar24) {
                iVar16 = iVar24 + 1;
                iVar10 = iVar24 + 3;
                iVar22 = ((iVar17 - iVar24) - 4U >> 2) + 1;
                iVar24 = iVar24 + iVar22 * 4;
                pfVar13 = pfVar7 + iVar16;
                pfVar15 = pfVar23 + iVar28 + iVar10;
                do {
                  pfVar13[-1] = pfVar15[-3];
                  iVar22 = iVar22 + -1;
                  *pfVar13 = *(float *)((int)pfVar23 + (iVar28 * 4 - (int)pfVar7) + -0x10 +
                                       (int)(pfVar13 + 4));
                  pfVar13[1] = pfVar15[-1];
                  pfVar13[2] = *pfVar15;
                  pfVar13 = pfVar13 + 4;
                  pfVar15 = pfVar15 + 4;
                } while (iVar22 != 0);
              }
              if (iVar24 < iVar17) {
                iVar17 = iVar17 - iVar24;
                pfVar13 = pfVar7 + iVar24;
                do {
                  iVar17 = iVar17 + -1;
                  *pfVar13 = *(float *)((int)pfVar13 + (int)pfVar23 + (iVar28 * 4 - (int)pfVar7));
                  pfVar13 = pfVar13 + 1;
                } while (iVar17 != 0);
              }
            }
          }
        }
        else if (param_1->W == 0) {
          pfVar13 = _vorbis_window_get(*(int *)((int)pvVar5 + 4) - iVar19);
          pfVar7 = param_1->pcm[local_38] + ((int)uVar27 / 2 - iVar25 / 2) + local_2c;
          pfVar23 = param_2->pcm[local_38];
          iVar24 = 0;
          if (3 < iVar25) {
            pfVar15 = pfVar7 + 1;
            iVar28 = iVar24;
            pfVar18 = pfVar13 + 2;
            pfVar26 = pfVar13 + iVar25 + -2;
            do {
              pfVar14 = (float *)(((int)pfVar13 - (int)pfVar7) + (int)pfVar15);
              iVar24 = iVar28 + 4;
              pfVar15[-1] = pfVar26[1] * pfVar15[-1] + pfVar23[iVar28] * pfVar18[-2];
              *pfVar15 = *pfVar26 * *pfVar15 +
                         *(float *)(((int)pfVar23 - (int)pfVar13) + (int)pfVar14) * *pfVar14;
              pfVar15[1] = pfVar26[-1] * pfVar15[1] +
                           *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
              pfVar15[2] = pfVar26[-2] * pfVar15[2] + pfVar23[iVar28 + 3] * pfVar18[1];
              pfVar15 = pfVar15 + 4;
              iVar28 = iVar24;
              pfVar18 = pfVar18 + 4;
              pfVar26 = pfVar26 + -4;
            } while (iVar24 < iVar25 + -3);
          }
          if (iVar24 < iVar25) {
            iVar28 = iVar25 - iVar24;
            pfVar15 = pfVar7 + iVar24;
            local_10 = pfVar13 + (iVar25 - iVar24) + -1;
            do {
              pfVar18 = (float *)((int)pfVar15 + ((int)pfVar13 - (int)pfVar7));
              iVar28 = iVar28 + -1;
              *pfVar15 = *pfVar15 * *local_10 +
                         *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
              pfVar15 = pfVar15 + 1;
              local_10 = local_10 + -1;
            } while (iVar28 != 0);
          }
        }
        else {
          pfVar13 = _vorbis_window_get(*(int *)((int)pvVar5 + 8) - iVar19);
          pfVar7 = param_1->pcm[local_38] + local_2c;
          pfVar23 = param_2->pcm[local_38];
          iVar24 = 0;
          if (3 < (int)uVar27) {
            pfVar15 = pfVar7 + 1;
            iVar28 = iVar24;
            pfVar18 = pfVar13 + 2;
            pfVar26 = pfVar13 + (uVar27 - 2);
            do {
              pfVar14 = (float *)(((int)pfVar13 - (int)pfVar7) + (int)pfVar15);
              iVar24 = iVar28 + 4;
              pfVar15[-1] = pfVar26[1] * pfVar15[-1] + pfVar23[iVar28] * pfVar18[-2];
              *pfVar15 = *pfVar26 * *pfVar15 +
                         *(float *)((int)pfVar14 + ((int)pfVar23 - (int)pfVar13)) * *pfVar14;
              pfVar15[1] = pfVar26[-1] * pfVar15[1] +
                           *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
              pfVar15[2] = pfVar26[-2] * pfVar15[2] + pfVar23[iVar28 + 3] * pfVar18[1];
              pfVar15 = pfVar15 + 4;
              iVar28 = iVar24;
              pfVar18 = pfVar18 + 4;
              pfVar26 = pfVar26 + -4;
            } while (iVar24 < (int)(uVar27 - 3));
          }
          if (iVar24 < (int)uVar27) {
            iVar28 = uVar27 - iVar24;
            pfVar15 = pfVar7 + iVar24;
            local_18 = pfVar13 + (uVar27 - iVar24) + -1;
            do {
              pfVar18 = (float *)((int)pfVar15 + ((int)pfVar13 - (int)pfVar7));
              iVar28 = iVar28 + -1;
              *pfVar15 = *pfVar15 * *local_18 +
                         *(float *)((int)pfVar18 + ((int)pfVar23 - (int)pfVar13)) * *pfVar18;
              pfVar15 = pfVar15 + 1;
              local_18 = local_18 + -1;
            } while (iVar28 != 0);
          }
        }
        pfVar23 = param_1->pcm[local_38] + local_14;
        pfVar7 = param_2->pcm[local_38];
        iVar24 = 0;
        if (3 < iVar12) {
          iVar28 = (iVar12 - 4U >> 2) + 1;
          iVar24 = iVar28 * 4;
          pfVar13 = pfVar23 + 1;
          pfVar15 = pfVar7 + iVar12 + 3;
          do {
            pfVar13[-1] = pfVar15[-3];
            iVar28 = iVar28 + -1;
            *pfVar13 = *(float *)((int)pfVar7 + (iVar12 * 4 - (int)pfVar23) + -0x10 +
                                 (int)(pfVar13 + 4));
            pfVar13[1] = pfVar15[-1];
            pfVar13[2] = *pfVar15;
            pfVar13 = pfVar13 + 4;
            pfVar15 = pfVar15 + 4;
          } while (iVar28 != 0);
        }
        if (iVar24 < iVar12) {
          iVar28 = iVar12 - iVar24;
          pfVar13 = pfVar23 + iVar24;
          do {
            iVar28 = iVar28 + -1;
            *pfVar13 = *(float *)((int)pfVar13 + (int)pfVar7 + (iVar12 * 4 - (int)pfVar23));
            pfVar13 = pfVar13 + 1;
          } while (iVar28 != 0);
        }
        local_38 = local_38 + 1;
      } while (local_38 < pvVar3->channels);
    }
    param_1->centerW = ~-(uint)(param_1->centerW != 0) & uVar27;
    if (param_1->pcm_returned == -1) {
      param_1->pcm_returned = local_14;
      param_1->pcm_current = local_14;
    }
    else {
      param_1->pcm_returned = local_2c;
      param_1->pcm_current =
           (((int)(piVar4[param_1->W] + (piVar4[param_1->W] >> 0x1f & 3U)) >> 2) +
            ((int)(piVar4[param_1->lW] + (piVar4[param_1->lW] >> 0x1f & 3U)) >> 2) >> (bVar9 & 0x1f)
           ) + local_2c;
    }
  }
  uVar6 = *(uint *)((int)pvVar5 + 0x80);
  if ((uVar6 & *(uint *)((int)pvVar5 + 0x84)) == 0xffffffff) {
    *(undefined4 *)((int)pvVar5 + 0x80) = 0;
    *(undefined4 *)((int)pvVar5 + 0x84) = 0;
  }
  else {
    uVar27 = ((int)(piVar4[param_1->lW] + (piVar4[param_1->lW] >> 0x1f & 3U)) >> 2) +
             ((int)(piVar4[param_1->W] + (piVar4[param_1->W] >> 0x1f & 3U)) >> 2);
    *(uint *)((int)pvVar5 + 0x80) = uVar27 + uVar6;
    *(uint *)((int)pvVar5 + 0x84) =
         ((int)uVar27 >> 0x1f) + *(uint *)((int)pvVar5 + 0x84) + (uint)CARRY4(uVar27,uVar6);
  }
  uVar6 = (uint)param_1->granulepos;
  uVar27 = *(uint *)((int)&param_1->granulepos + 4);
  if ((uVar6 & uVar27) == 0xffffffff) {
    uVar6 = (uint)param_2->granulepos;
    uVar27 = *(uint *)((int)&param_2->granulepos + 4);
    if ((uVar6 & uVar27) != 0xffffffff) {
      *(uint *)&param_1->granulepos = uVar6;
      *(uint *)((int)&param_1->granulepos + 4) = uVar27;
      iVar19 = *(int *)((int)&param_1->granulepos + 4);
      if ((iVar19 <= *(int *)((int)pvVar5 + 0x84)) &&
         ((iVar19 < *(int *)((int)pvVar5 + 0x84) ||
          ((uint)param_1->granulepos < *(uint *)((int)pvVar5 + 0x80))))) {
        iVar19 = *(int *)((int)pvVar5 + 0x80) - (int)param_2->granulepos;
        if (iVar19 < 0) {
          iVar19 = 0;
        }
        if (param_2->eofflag == 0) {
          param_1->pcm_returned = param_1->pcm_returned + (iVar19 >> (bVar9 & 0x1f));
          if (param_1->pcm_current < param_1->pcm_returned) {
            param_1->pcm_returned = param_1->pcm_current;
          }
        }
        else {
          iVar12 = param_1->pcm_current - param_1->pcm_returned << (bVar9 & 0x1f);
          if (iVar12 < iVar19) {
            iVar19 = iVar12;
          }
          param_1->pcm_current = param_1->pcm_current - (iVar19 >> (bVar9 & 0x1f));
        }
      }
    }
  }
  else {
    uVar20 = ((int)(piVar4[param_1->lW] + (piVar4[param_1->lW] >> 0x1f & 3U)) >> 2) +
             ((int)(piVar4[param_1->W] + (piVar4[param_1->W] >> 0x1f & 3U)) >> 2);
    *(uint *)((int)&param_1->granulepos + 4) =
         ((int)uVar20 >> 0x1f) + uVar27 + (uint)CARRY4(uVar20,uVar6);
    *(uint *)&param_1->granulepos = uVar20 + uVar6;
    uVar6 = (uint)param_2->granulepos;
    uVar27 = *(uint *)((int)&param_2->granulepos + 4);
    if ((uVar6 & uVar27) != 0xffffffff) {
      uVar20 = (uint)param_1->granulepos;
      uVar8 = *(uint *)((int)&param_1->granulepos + 4);
      if ((uVar20 != uVar6) || (uVar8 != uVar27)) {
        if (((((int)uVar27 <= (int)uVar8) && (((int)uVar27 < (int)uVar8 || (uVar6 < uVar20)))) &&
            (iVar19 = (int)param_1->granulepos - (int)param_2->granulepos, iVar19 != 0)) &&
           (param_2->eofflag != 0)) {
          iVar12 = param_1->pcm_current - param_1->pcm_returned << (bVar9 & 0x1f);
          if (iVar12 < iVar19) {
            iVar19 = iVar12;
          }
          if (iVar19 < 0) {
            iVar19 = 0;
          }
          param_1->pcm_current = param_1->pcm_current - (iVar19 >> (bVar9 & 0x1f));
        }
        *(int *)&param_1->granulepos = (int)param_2->granulepos;
        *(undefined4 *)((int)&param_1->granulepos + 4) =
             *(undefined4 *)((int)&param_2->granulepos + 4);
      }
    }
  }
  if (param_2->eofflag != 0) {
    param_1->eofflag = 1;
  }
  return 0;
}
