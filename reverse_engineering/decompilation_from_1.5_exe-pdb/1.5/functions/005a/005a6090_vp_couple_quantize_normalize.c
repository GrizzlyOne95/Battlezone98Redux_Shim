/*
 * Entry: 005a6090
 * Name: _vp_couple_quantize_normalize
 * Namespace: Global
 * Signature: void _vp_couple_quantize_normalize(int param_1, vorbis_info_psy_global * param_2, vorbis_look_psy * param_3, vorbis_info_mapping0 * param_4, float * * param_5, int * * param_6, int * param_7, int param_8, int param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl
_vp_couple_quantize_normalize
          (int param_1,vorbis_info_psy_global *param_2,vorbis_look_psy *param_3,
          vorbis_info_mapping0 *param_4,float **param_5,int **param_6,int *param_7,int param_8,
          int param_9)

{
  int iVar1;
  double dVar2;
  double dVar3;
  vorbis_info_psy *pvVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  int iVar15;
  undefined4 *puVar16;
  int iVar17;
  int *piVar18;
  int iVar19;
  float *pfVar20;
  float *pfVar21;
  int iVar22;
  int *piVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  undefined4 *puVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  float fVar34;
  int aiStack_d0 [4];
  float afStack_c0 [2];
  int iStack_b8;
  float fStack_b4;
  int iStack_b0;
  float local_78;
  int local_58;
  int local_50;
  int local_48;
  int local_44;
  int local_40;
  int local_2c;
  float *local_20;
  float *local_1c;
  int *local_18;
  
  iVar28 = param_3->n;
  pvVar4 = param_3->vi;
  if (pvVar4->normal_p == 0) {
    local_48 = 0x10;
  }
  else {
    local_48 = pvVar4->normal_partition;
  }
  iVar5 = param_2->coupling_pointlimit[pvVar4->blockflag][param_1];
  iVar29 = param_2->coupling_postpointamp[param_1];
  dVar2 = stereo_threshholds[param_2->coupling_prepointamp[param_1]];
  dVar3 = stereo_threshholds[iVar29];
  iStack_b0 = 0x5a6118;
  iVar9 = param_9 * -4;
  piVar18 = (int *)(&stack0xffffff54 + param_9 * -8);
  iVar12 = param_9 * -0x14;
  (&iStack_b0)[-param_9] = 0x5a6122;
  (&iStack_b0)[param_9 * -2] = 0x5a612e;
  (&iStack_b0)[param_9 * -3] = 0x5a613a;
  (&iStack_b0)[param_9 * -4] = 0x5a6144;
  iVar1 = param_4->coupling_steps + param_9;
  (&iStack_b0)[param_9 * -5] = 0x5a6162;
  iVar10 = iVar1 * -4;
  puVar30 = (undefined4 *)(&stack0xffffff54 + iVar10 + param_9 * -0x14);
  if (1000 < iVar28) {
    dVar3 = stereo_threshholds_limited[iVar29];
  }
  local_78 = (float)dVar3;
  iVar29 = local_48 * param_9;
  (&iStack_b0)[param_9 * -5 - iVar1] = 0x5a618f;
  *(undefined1 **)(&stack0xffffff54 + iVar9) =
       &stack0xffffff54 + iVar29 * -4 + iVar10 + param_9 * -0x14;
  (&iStack_b0)[param_9 * -5 + (-iVar1 - iVar29)] = 0x5a619d;
  *(undefined1 **)(&stack0xffffff54 + param_9 * -8) =
       &stack0xffffff54 + iVar29 * -8 + iVar10 + param_9 * -0x14;
  (&iStack_b0)[param_9 * -5 + (iVar29 * -2 - iVar1)] = 0x5a61a8;
  *(undefined1 **)(&stack0xffffff54 + param_9 * -0xc) =
       &stack0xffffff54 + iVar29 * -0xc + iVar10 + iVar12;
  (&iStack_b0)[param_9 * -5 + (iVar29 * -3 - iVar1)] = 0x5a61b3;
  *(undefined1 **)(&stack0xffffff54 + param_9 * -0x10) =
       &stack0xffffff54 + iVar29 * -0x10 + iVar10 + iVar12;
  if (1 < param_9) {
    param_1 = param_9 + -1;
    iVar13 = local_48 * 4;
    do {
      piVar18 = piVar18 + 1;
      piVar18[param_9] = *(int *)(&stack0xffffff54 + iVar9) + iVar13;
      *piVar18 = *(int *)(&stack0xffffff54 + param_9 * -8) + iVar13;
      piVar18[-param_9] = *(int *)(&stack0xffffff54 + param_9 * -0xc) + iVar13;
      iVar22 = *(int *)(&stack0xffffff54 + param_9 * -0x10) + iVar13;
      iVar13 = iVar13 + local_48 * 4;
      piVar18[param_9 * -2] = iVar22;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  iVar13 = iVar1;
  if (0 < iVar1) {
    for (; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar30 = 0;
      puVar30 = puVar30 + 1;
    }
  }
  local_44 = 0;
  if (0 < iVar28) {
    uVar6 = *(undefined4 *)(&stack0xffffff54 + param_9 * -0x10);
    local_2c = 0;
    local_58 = iVar28;
    do {
      param_1 = local_58;
      if (local_48 <= local_58) {
        param_1 = local_48;
      }
      (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)] = param_9 * 4;
      (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)param_7;
      (&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (int)(&stack0xffffff54 + param_9 * -0x14)
      ;
      afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = 8.300569e-39;
      memcpy();
      afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = (float)(iVar29 * 4);
      afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)] = 0.0;
      afStack_c0[param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)] = (float)uVar6;
      aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)] = 0x5a62aa;
      memset();
      iVar13 = 0;
      if (0 < param_9) {
        iVar22 = (int)param_5 - (int)(&stack0xffffff54 + param_9 * -0xc);
        local_50 = param_9;
        piVar18 = (int *)(&stack0xffffff54 + param_9 * -0xc);
        do {
          iVar13 = *(int *)((int)piVar18 +
                            (int)(&stack0xffffff54 + (param_9 * -0x14 - (int)param_5) + iVar22) +
                           ((int)param_6 - (int)(&stack0xffffff54 + param_9 * -0x14))) + local_2c;
          if (*(int *)((int)piVar18 +
                      (int)(&stack0xffffff54 + (param_9 * -0x14 - (int)param_5) + iVar22)) == 0) {
            if (0 < param_1) {
              puVar30 = (undefined4 *)piVar18[param_9 * 2];
              iVar25 = *piVar18;
              iVar15 = piVar18[param_9];
              iVar19 = piVar18[-param_9];
              param_2 = (vorbis_info_psy_global *)param_1;
              puVar16 = puVar30;
              do {
                *(undefined4 *)((int)puVar16 + (iVar25 - (int)puVar30)) = 0x2edbe6ff;
                param_2 = (vorbis_info_psy_global *)((int)param_2[-1].sliding_lowpass[1] + 0x3b);
                *puVar16 = 0;
                *(undefined4 *)((iVar15 - (int)puVar30) + -4 + (int)(puVar16 + 1)) = 0;
                *(undefined4 *)((int)puVar16 + (iVar19 - (int)puVar30)) = 0;
                *(undefined4 *)((int)puVar16 + (iVar13 - (int)puVar30)) = 0;
                puVar16 = puVar16 + 1;
              } while (param_2 != (vorbis_info_psy_global *)0x0);
            }
            piVar18[param_9 * -2 - iVar1] = 0;
          }
          else {
            iVar25 = 0;
            if (3 < param_1) {
              iVar15 = *piVar18;
              iVar19 = (param_1 - 4U >> 2) + 1;
              iVar25 = iVar19 * 4;
              pfVar14 = (float *)(iVar15 + 4);
              piVar23 = (int *)(iVar13 + 0xc);
              do {
                pfVar14[-1] = FLOOR1_fromdB_LOOKUP[piVar23[-3]];
                *pfVar14 = FLOOR1_fromdB_LOOKUP[*(int *)((int)pfVar14 + (iVar13 - iVar15))];
                iVar19 = iVar19 + -1;
                pfVar14[1] = FLOOR1_fromdB_LOOKUP[piVar23[-1]];
                pfVar14[2] = FLOOR1_fromdB_LOOKUP[*piVar23];
                pfVar14 = pfVar14 + 4;
                piVar23 = piVar23 + 4;
              } while (iVar19 != 0);
            }
            if (iVar25 < param_1) {
              iVar15 = *piVar18;
              iVar19 = param_1 - iVar25;
              pfVar14 = (float *)(iVar15 + iVar25 * 4);
              do {
                iVar19 = iVar19 + -1;
                *pfVar14 = FLOOR1_fromdB_LOOKUP[*(int *)((iVar13 - iVar15) + (int)pfVar14)];
                pfVar14 = pfVar14 + 1;
              } while (iVar19 != 0);
            }
            iVar15 = *piVar18;
            (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)] = param_1;
            iVar25 = *(int *)(iVar22 + (int)piVar18);
            (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)local_44;
            (&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)] = iVar25 + local_2c;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = local_78;
            afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)dVar2;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)] = (float)iVar5;
            aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)] = 0x5a63ff;
            flag_lossless((int)afStack_c0[param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)],
                          afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)],
                          afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)],
                          (float *)(&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                          (float *)(&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                          (int *)(&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                          *(int *)(&stack0xffffff54 + iVar29 * -0x10 + iVar10 + iVar12),
                          *(int *)(&stack0xffffff58 + iVar29 * -0x10 + iVar10 + iVar12));
            iVar25 = 0;
            if (3 < param_1) {
              iVar25 = *(int *)(iVar22 + (int)piVar18);
              local_20 = (float *)piVar18[param_9];
              pfVar14 = (float *)(iVar15 + 8);
              pfVar21 = (float *)(iVar25 + 8 + local_2c);
              local_1c = (float *)(iVar25 + 4 + local_2c);
              iVar19 = (int)local_20 - piVar18[param_9 * 2];
              iVar26 = *piVar18 - piVar18[param_9 * 2];
              iVar15 = (int)local_20 - *piVar18;
              pfVar20 = (float *)(piVar18[param_9 * 2] + 4);
              iVar31 = (param_1 - 4U >> 2) + 1;
              iVar25 = iVar31 * 4;
              do {
                fVar34 = pfVar21[-2] * pfVar21[-2];
                pfVar20[-1] = fVar34;
                *local_20 = fVar34;
                if (pfVar21[-2] < 0.0) {
                  pfVar20[-1] = pfVar20[-1] * -1.0;
                }
                pfVar14[-2] = pfVar14[-2] * pfVar14[-2];
                fVar34 = *local_1c * *local_1c;
                *pfVar20 = fVar34;
                *(float *)(iVar19 + (int)pfVar20) = fVar34;
                if (*local_1c < 0.0) {
                  *pfVar20 = *pfVar20 * -1.0;
                }
                fVar34 = *(float *)((int)pfVar20 + iVar26);
                *(float *)((int)pfVar20 + iVar26) = fVar34 * fVar34;
                fVar34 = *pfVar21 * *pfVar21;
                pfVar20[1] = fVar34;
                *(float *)((int)pfVar14 + iVar15) = fVar34;
                if (*pfVar21 < 0.0) {
                  pfVar20[1] = pfVar20[1] * -1.0;
                }
                *pfVar14 = *pfVar14 * *pfVar14;
                fVar34 = pfVar21[1] * pfVar21[1];
                pfVar20[2] = fVar34;
                local_20[3] = fVar34;
                if (pfVar21[1] < 0.0) {
                  pfVar20[2] = pfVar20[2] * -1.0;
                }
                local_20 = local_20 + 4;
                local_1c = local_1c + 4;
                pfVar20 = pfVar20 + 4;
                pfVar21 = pfVar21 + 4;
                pfVar14[1] = pfVar14[1] * pfVar14[1];
                pfVar14 = pfVar14 + 4;
                iVar31 = iVar31 + -1;
              } while (iVar31 != 0);
            }
            if (iVar25 < param_1) {
              iVar15 = piVar18[param_9 * 2];
              pfVar14 = (float *)(*(int *)(iVar22 + (int)piVar18) + (iVar25 + local_44) * 4);
              iVar19 = *piVar18;
              iVar26 = piVar18[param_9];
              iVar31 = param_1 - iVar25;
              pfVar21 = (float *)(iVar15 + iVar25 * 4);
              do {
                fVar34 = *pfVar14 * *pfVar14;
                *pfVar21 = fVar34;
                *(float *)((iVar26 - iVar15) + (int)pfVar21) = fVar34;
                if (*pfVar14 < 0.0) {
                  *pfVar21 = *pfVar21 * -1.0;
                }
                fVar34 = *(float *)((int)pfVar21 + (iVar19 - iVar15));
                pfVar14 = pfVar14 + 1;
                iVar31 = iVar31 + -1;
                *(float *)((int)pfVar21 + (iVar19 - iVar15)) = fVar34 * fVar34;
                pfVar21 = pfVar21 + 1;
              } while (iVar31 != 0);
            }
            iVar25 = piVar18[param_9 * -2 - iVar1];
            iVar15 = *piVar18;
            (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)] = iVar13;
            (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)param_1;
            (&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)] = local_44;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = (float)param_1;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = (float)iVar25;
            afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)] = 0.0;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)] = (float)iVar15;
            aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)] = piVar18[param_9 * 2];
            aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = iVar5;
            aiStack_d0[param_9 * -5 + (iVar29 * -4 - iVar1)] = 0x5a65fa;
            fVar34 = noise_normalize((vorbis_look_psy *)
                                     aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)],
                                     aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)],
                                     (float *)afStack_c0
                                              [param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)],
                                     (float *)afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (float *)afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)]
                                     ,(int *)(&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     *(int *)(&stack0xffffff54 + iVar29 * -0x10 + iVar10 + iVar12),
                                     *(int **)(&stack0xffffff58 + iVar29 * -0x10 + iVar10 + iVar12))
            ;
            piVar18[param_9 * -2 - iVar1] = (int)fVar34;
          }
          piVar18 = piVar18 + 1;
          local_50 = local_50 + -1;
          iVar13 = param_9;
        } while (local_50 != 0);
      }
      local_40 = 0;
      if (0 < param_4->coupling_steps) {
        local_20 = (float *)(&stack0xffffff54 + iVar13 * 4 + iVar10 + param_9 * -0x14);
        local_18 = param_4->coupling_ang;
        do {
          iVar13 = local_18[-0x100];
          iVar22 = *local_18;
          piVar18 = param_6[iVar13];
          piVar23 = param_6[iVar22];
          pfVar14 = *(float **)(&stack0xffffff54 + iVar13 * 4 + iVar9);
          iVar25 = *(int *)(&stack0xffffff54 + iVar22 * 4 + iVar9);
          iVar15 = *(int *)(&stack0xffffff54 + iVar13 * 4 + param_9 * -8);
          iVar19 = *(int *)(&stack0xffffff54 + iVar22 * 4 + param_9 * -8);
          iVar26 = *(int *)(&stack0xffffff54 + iVar13 * 4 + param_9 * -0xc);
          iVar31 = *(int *)(&stack0xffffff54 + iVar22 * 4 + param_9 * -0xc);
          iVar7 = *(int *)(&stack0xffffff54 + iVar13 * 4 + param_9 * -0x10);
          iVar17 = *(int *)(&stack0xffffff54 + iVar22 * 4 + param_9 * -0x10);
          if ((*(int *)(&stack0xffffff54 + iVar13 * 4 + param_9 * -0x14) != 0) ||
             (*(int *)(&stack0xffffff54 + iVar22 * 4 + param_9 * -0x14) != 0)) {
            *(undefined4 *)(&stack0xffffff54 + iVar22 * 4 + param_9 * -0x14) = 1;
            *(undefined4 *)(&stack0xffffff54 + iVar13 * 4 + param_9 * -0x14) = 1;
            param_2 = (vorbis_info_psy_global *)0x0;
            if (0 < param_1) {
              iVar25 = iVar25 - (int)pfVar14;
              iVar15 = iVar15 - (int)pfVar14;
              iVar17 = iVar17 - (int)pfVar14;
              iVar13 = iVar7 - (int)pfVar14;
              iVar27 = (int)piVar23 + (local_2c - (int)pfVar14);
              iVar32 = ((int)piVar18 + local_2c) - (int)pfVar14;
              iVar22 = iVar26 - (int)pfVar14;
              pfVar21 = pfVar14;
              do {
                if ((int)param_2 < (param_8 - iVar28) + local_58) {
                  if ((*(int *)(iVar13 + (int)pfVar21) == 0) &&
                     (*(int *)(iVar17 + (int)pfVar21) == 0)) {
                    fVar34 = *(float *)(iVar25 + (int)pfVar21) + *pfVar21;
                    if ((int)param_2 < (iVar5 - iVar28) + local_58) {
                      *pfVar21 = fVar34;
                      *(float *)(iVar15 + (int)pfVar21) = ABS(fVar34);
                    }
                    else {
                      fVar11 = ABS(*pfVar21) + ABS(*(float *)(iVar25 + (int)pfVar21));
                      *(float *)(iVar15 + (int)pfVar21) = fVar11;
                      if (fVar34 < 0.0) {
                        fVar11 = -fVar11;
                      }
                      *pfVar21 = fVar11;
                    }
                    *(undefined4 *)((iVar19 - (int)pfVar14) + (int)pfVar21) = 0;
                    *(undefined4 *)(iVar25 + (int)pfVar21) = 0;
                    *(undefined4 *)(iVar17 + (int)pfVar21) = 1;
                    *(undefined4 *)(iVar27 + (int)pfVar21) = 0;
                  }
                  else {
                    *pfVar21 = ABS(*pfVar21) + ABS(*(float *)(iVar25 + (int)pfVar21));
                    *(float *)(iVar15 + (int)pfVar21) =
                         *(float *)((iVar19 - (int)pfVar14) + (int)pfVar21) +
                         *(float *)(iVar15 + (int)pfVar21);
                    *(undefined4 *)(iVar17 + (int)pfVar21) = 1;
                    *(undefined4 *)(iVar13 + (int)pfVar21) = 1;
                    uVar24 = *(uint *)(iVar27 + (int)pfVar21);
                    uVar8 = *(uint *)(iVar32 + (int)pfVar21);
                    if ((int)((uVar24 ^ (int)uVar24 >> 0x1f) - ((int)uVar24 >> 0x1f)) <
                        (int)((uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f))) {
                      if ((int)uVar8 < 1) {
                        *(uint *)(iVar27 + (int)pfVar21) = uVar24 - uVar8;
                      }
                      else {
                        *(uint *)(iVar27 + (int)pfVar21) = uVar8 - uVar24;
                      }
                    }
                    else {
                      if ((int)uVar24 < 1) {
                        iVar33 = uVar24 - uVar8;
                      }
                      else {
                        iVar33 = uVar8 - uVar24;
                      }
                      *(int *)(iVar27 + (int)pfVar21) = iVar33;
                      *(uint *)(iVar32 + (int)pfVar21) = uVar24;
                    }
                    uVar24 = (int)*(uint *)(iVar32 + (int)pfVar21) >> 0x1f;
                    if ((int)(((*(uint *)(iVar32 + (int)pfVar21) ^ uVar24) - uVar24) * 2) <=
                        *(int *)(iVar27 + (int)pfVar21)) {
                      *(int *)(iVar27 + (int)pfVar21) = -*(int *)(iVar27 + (int)pfVar21);
                      *(int *)(iVar32 + (int)pfVar21) = -*(int *)(iVar32 + (int)pfVar21);
                    }
                  }
                }
                fVar34 = *(float *)(iVar22 + (int)pfVar21) +
                         *(float *)((iVar31 - (int)pfVar14) + (int)pfVar21);
                pfVar21 = pfVar21 + 1;
                *(float *)((iVar31 - (int)pfVar14) + -4 + (int)pfVar21) = fVar34;
                param_2 = (vorbis_info_psy_global *)((int)&param_2->eighth_octave_lines + 1);
                *(float *)(iVar22 + -4 + (int)pfVar21) = fVar34;
              } while ((int)param_2 < param_1);
            }
            fVar34 = *local_20;
            (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (int)piVar18 + local_2c;
            (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)param_1;
            (&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)] = local_44;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = (float)param_1;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = fVar34;
            afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)] = (float)iVar7;
            afStack_c0[param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)] = (float)iVar26;
            aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)] = (int)pfVar14;
            aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)] = iVar5;
            aiStack_d0[param_9 * -5 + (iVar29 * -4 - iVar1)] = 0x5a6934;
            fVar34 = noise_normalize((vorbis_look_psy *)
                                     aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)],
                                     aiStack_d0[param_9 * -5 + ((iVar29 * -4 + 2) - iVar1)],
                                     (float *)afStack_c0
                                              [param_9 * -5 + ((iVar29 * -4 + -1) - iVar1)],
                                     (float *)afStack_c0[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (float *)afStack_c0[param_9 * -5 + ((iVar29 * -4 + 1) - iVar1)]
                                     ,(int *)(&iStack_b8)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (&fStack_b4)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     (&iStack_b0)[param_9 * -5 + (iVar29 * -4 - iVar1)],
                                     *(int *)(&stack0xffffff54 + iVar29 * -0x10 + iVar10 + iVar12),
                                     *(int **)(&stack0xffffff58 + iVar29 * -0x10 + iVar10 + iVar12))
            ;
            *local_20 = fVar34;
            local_20 = local_20 + 1;
          }
          local_18 = local_18 + 1;
          local_40 = local_40 + 1;
        } while (local_40 < param_4->coupling_steps);
      }
      local_58 = local_58 - local_48;
      local_44 = local_44 + local_48;
      local_2c = local_2c + local_48 * 4;
    } while (local_44 < iVar28);
  }
  iVar28 = 0;
  if (0 < param_4->coupling_steps) {
    piVar18 = param_4->coupling_ang;
    do {
      if ((param_7[piVar18[-0x100]] != 0) || (param_7[*piVar18] != 0)) {
        param_7[piVar18[-0x100]] = 1;
        param_7[*piVar18] = 1;
      }
      iVar28 = iVar28 + 1;
      piVar18 = piVar18 + 1;
    } while (iVar28 < param_4->coupling_steps);
  }
  return;
}
