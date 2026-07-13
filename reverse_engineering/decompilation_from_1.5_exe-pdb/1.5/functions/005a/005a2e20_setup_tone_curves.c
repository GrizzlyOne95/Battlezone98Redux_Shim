/*
 * Entry: 005a2e20
 * Name: setup_tone_curves
 * Namespace: Global
 * Signature: float * * * setup_tone_curves(float * param_1, float param_2, int param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

float *** __cdecl
setup_tone_curves(float *param_1,float param_2,int param_3,float param_4,float param_5)

{
  float ***pppfVar1;
  double dVar2;
  int extraout_EAX;
  float *extraout_EAX_00;
  float *extraout_EAX_01;
  float extraout_EAX_02;
  float extraout_EAX_03;
  float extraout_EAX_04;
  float *extraout_EAX_05;
  int extraout_EAX_06;
  float *in_ECX;
  int iVar3;
  float *pfVar4;
  float *extraout_ECX;
  float *pfVar5;
  uint uVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  float *pfVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  float fVar14;
  int iVar15;
  float *pfVar16;
  undefined4 *puVar17;
  float fVar18;
  float10 fVar19;
  int aiStack_7f54 [4];
  float fStack_7f44;
  float local_7f34 [55];
  float afStack_7e58 [7561];
  float local_834 [448];
  float local_134 [56];
  float **local_54;
  float **local_50;
  float **local_4c;
  double local_48;
  double local_40;
  float ***local_38;
  undefined8 local_34;
  int local_2c;
  float *local_28;
  float *local_24;
  float *local_20;
  undefined4 *local_1c;
  float *local_18;
  float *local_14;
  float *local_10;
  float *local_c;
  float local_8;
  
  local_8 = 8.28176e-39;
  fStack_7f44 = 8.281783e-39;
  local_1c = local_7f34 + (-3 - (int)param_2);
  (&fStack_7f44)[-(int)param_2] = 9.52883e-44;
  aiStack_7f54[3 - (int)param_2] = 0x5a2e49;
  local_38 = malloc((size_t)(&fStack_7f44)[-(int)param_2]);
  aiStack_7f54[3 - (int)param_2] = 0x7700;
  aiStack_7f54[2 - (int)param_2] = 0;
  aiStack_7f54[1 - (int)param_2] = (int)local_7f34;
  aiStack_7f54[-(int)param_2] = 0x5a2e5f;
  memset();
  pfVar9 = local_7f34 + (-3 - (int)param_2);
  local_10 = local_7f34;
  local_24 = (float *)tonemasks;
  local_28 = ATH + 1;
  local_14 = (float *)(2 - (int)in_ECX);
  local_18 = in_ECX;
  do {
    iVar3 = (int)local_14 + (int)local_18;
    pfVar5 = local_134;
    iVar15 = 0x38;
    pfVar4 = local_28;
    do {
      local_8 = 999.0;
      if (iVar3 + -2 < 0x58) {
        if (pfVar4[-1] < 999.0) {
          local_8 = pfVar4[-1];
        }
      }
      else {
        local_8 = -30.0;
      }
      if (iVar3 + -1 < 0x58) {
        if (*pfVar4 < local_8) {
          local_8 = *pfVar4;
        }
      }
      else if (-30.0 < local_8) {
        local_8 = -30.0;
      }
      if (iVar3 < 0x58) {
        if (pfVar4[1] < local_8) {
          local_8 = pfVar4[1];
        }
      }
      else if (-30.0 < local_8) {
        local_8 = -30.0;
      }
      iVar3 = iVar3 + 1;
      if (iVar3 < 0x58) {
        if (pfVar4[2] < local_8) {
          local_8 = pfVar4[2];
        }
      }
      else if (-30.0 < local_8) {
        local_8 = -30.0;
      }
      pfVar4 = pfVar4 + 1;
      *pfVar5 = local_8;
      pfVar5 = pfVar5 + 1;
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
    pfVar5 = local_24;
    pfVar4 = local_10 + 0x70;
    for (iVar3 = 0x150; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar5 = local_24;
    pfVar4 = local_10;
    for (iVar3 = 0x38; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar4 = pfVar4 + 1;
    }
    local_34 = (double)CONCAT44(local_10 + 0x38,(undefined4)local_34);
    pfVar5 = local_24;
    pfVar4 = local_10 + 0x38;
    for (iVar3 = 0x38; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar4 = pfVar4 + 1;
    }
    iVar3 = 8;
    uVar13 = 0xf;
    pfVar5 = local_10 + 1;
    while( true ) {
      do {
        uVar6 = (int)(uVar13 + 1) >> 0x1f;
        local_8 = (float)(int)((uVar13 + 1 ^ uVar6) - uVar6) * param_4 + (float)param_3;
        if ((0.0 <= local_8) || ((float)param_3 <= 0.0)) {
          if ((0.0 < local_8) && ((float)param_3 < 0.0)) {
            local_8 = 0.0;
          }
        }
        else {
          local_8 = 0.0;
        }
        pfVar5[-1] = pfVar5[-1] + local_8;
        local_8 = (float)(int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) * param_4 +
                  (float)param_3;
        if (((local_8 < 0.0) && (0.0 < (float)param_3)) ||
           ((0.0 < local_8 && ((float)param_3 < 0.0)))) {
          local_8 = 0.0;
        }
        uVar6 = (int)(uVar13 - 1) >> 0x1f;
        *pfVar5 = *pfVar5 + local_8;
        local_8 = (float)(int)((uVar13 - 1 ^ uVar6) - uVar6) * param_4 + (float)param_3;
        if (((local_8 < 0.0) && (0.0 < (float)param_3)) ||
           ((0.0 < local_8 && ((float)param_3 < 0.0)))) {
          local_8 = 0.0;
        }
        uVar6 = (int)(uVar13 - 2) >> 0x1f;
        pfVar5[1] = pfVar5[1] + local_8;
        local_8 = (float)(int)((uVar13 - 2 ^ uVar6) - uVar6) * param_4 + (float)param_3;
        if (((local_8 < 0.0) && (0.0 < (float)param_3)) ||
           ((0.0 < local_8 && ((float)param_3 < 0.0)))) {
          local_8 = 0.0;
        }
        uVar13 = uVar13 - 4;
        pfVar4 = pfVar5 + 4;
        pfVar5[2] = pfVar5[2] + local_8;
        pfVar5 = pfVar4;
      } while (-0x29 < (int)uVar13);
      iVar3 = iVar3 + -1;
      if (iVar3 == 0) break;
      uVar13 = 0xf;
    }
    local_8 = (float)iVar3;
    pfVar5 = local_834;
    local_40 = (double)(*local_18 + 100.0);
    pfVar4 = local_18;
    do {
      local_c = (float *)0x2;
      if (1 < (int)local_8) {
        local_c = (float *)local_8;
      }
      (&fStack_7f44)[-(int)param_2] = (float)pfVar4;
      local_c = (float *)(((float)local_40 - (float)(int)local_c * 10.0) - 30.0);
      (&fStack_7f44)[-(int)param_2] = (float)local_c;
      aiStack_7f54[3 - (int)param_2] = 0x5a31f0;
      attenuate_curve((float *)(&fStack_7f44)[-(int)param_2],local_7f34[-3 - (int)param_2]);
      fVar14 = (float)(int)local_8;
      pfVar4 = local_134;
      pfVar16 = pfVar5;
      for (iVar3 = 0x38; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pfVar16 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar16 = pfVar16 + 1;
      }
      local_c = (float *)((100.0 - fVar14 * 10.0) - 30.0);
      (&fStack_7f44)[-(int)param_2] = (float)local_c;
      aiStack_7f54[3 - (int)param_2] = 0x5a3224;
      attenuate_curve((float *)(&fStack_7f44)[-(int)param_2],local_7f34[-3 - (int)param_2]);
      (&fStack_7f44)[-(int)param_2] = 8.283199e-39;
      max_curve((float *)local_7f34[-3 - (int)param_2],(float *)local_7f34[-2 - (int)param_2]);
      local_10 = local_10 + 0x38;
      local_8 = (float)((int)local_8 + 1);
      pfVar5 = pfVar5 + 0x38;
      pfVar4 = extraout_ECX;
    } while ((int)local_8 < 8);
    iVar3 = 7;
    do {
      (&fStack_7f44)[-(int)param_2] = 8.283284e-39;
      min_curve((float *)local_7f34[-3 - (int)param_2],(float *)local_7f34[-2 - (int)param_2]);
      (&fStack_7f44)[-(int)param_2] = 8.283297e-39;
      min_curve((float *)local_7f34[-3 - (int)param_2],(float *)local_7f34[-2 - (int)param_2]);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    local_24 = local_24 + 0x150;
    local_18 = local_18 + 1;
    local_28 = local_28 + 4;
  } while ((int)local_28 < 0x6126bc);
  local_14 = (float *)0x0;
  do {
    pfVar5 = local_14;
    *(undefined4 *)((int)pfVar9 + -4) = 0x20;
    *(undefined4 *)((int)pfVar9 + -8) = 0x5a32b9;
    local_50 = malloc(*(size_t *)((int)pfVar9 + -4));
    pppfVar1 = local_38;
    local_40 = (double)(int)local_14 * 0.5;
    local_38[(int)pfVar5] = local_50;
    puVar7 = (undefined1 *)((int)pfVar9 + -4);
    *(undefined4 *)((int)pfVar9 + -4) = 0x5a32e2;
    fVar19 = (float10)__CIexp();
    *(double *)(puVar7 + -8) = (double)(fVar19 / (float10)(float)param_1);
    *(undefined4 *)(puVar7 + -0xc) = 0x5a32f0;
    floor();
    *(undefined4 *)(puVar7 + -4) = 0x5a32f8;
    _ftol2_sse();
    puVar8 = puVar7 + -4;
    *(undefined4 *)(puVar7 + -4) = 0x5a330e;
    fVar19 = (float10)__CIlog();
    fVar19 = fVar19 * (float10)1.4426950216293335 - (float10)5.965784072875977;
    *(double *)(puVar8 + -8) = (double)(fVar19 + fVar19);
    *(undefined4 *)(puVar8 + -0xc) = 0x5a3328;
    ceil(*(double *)(puVar8 + -8));
    *(undefined4 *)(puVar8 + -4) = 0x5a3330;
    _ftol2_sse();
    local_14 = (float *)(extraout_EAX + 1);
    pfVar9 = (float *)(puVar8 + -4);
    *(undefined4 *)(puVar8 + -4) = 0x5a3342;
    local_10 = extraout_EAX_00;
    fVar19 = (float10)__CIlog();
    fVar19 = fVar19 * (float10)1.4426950216293335 - (float10)5.965784072875977;
    *(double *)((int)pfVar9 + -8) = (double)(fVar19 + fVar19);
    *(undefined4 *)((int)pfVar9 + -0xc) = 0x5a335b;
    floor();
    *(undefined4 *)((int)pfVar9 + -4) = 0x5a3363;
    _ftol2_sse();
    local_24 = extraout_EAX_01;
    if ((int)pfVar5 < (int)local_10) {
      local_10 = pfVar5;
    }
    if ((int)local_10 < 0) {
      local_10 = (float *)0x0;
    }
    if (0x10 < (int)extraout_EAX_01) {
      local_24 = (float *)0x10;
    }
    local_2c = 0;
    local_18 = (float *)((int)pfVar5 + 1);
    local_4c = pppfVar1[(int)pfVar5];
    local_54 = pppfVar1[(int)pfVar5];
    do {
      *(undefined4 *)((int)pfVar9 + -4) = 0xe8;
      *(undefined4 *)((int)pfVar9 + -8) = 0x5a33ab;
      local_14 = malloc(*(size_t *)((int)pfVar9 + -4));
      local_50[local_2c] = local_14;
      fVar14 = param_2;
      puVar17 = local_1c;
      if (0 < (int)param_2) {
        for (; fVar14 != 0.0; fVar14 = (float)((int)fVar14 + -1)) {
          *puVar17 = 0x4479c000;
          puVar17 = puVar17 + 1;
        }
      }
      local_c = local_10;
      if ((int)local_10 <= (int)local_24) {
        iVar3 = local_2c + (int)local_10 * 8;
        local_28 = (float *)(iVar3 * 0x38);
        local_20 = afStack_7e58 + iVar3 * 0x38;
        do {
          fVar14 = 0.0;
          local_8 = 0.0;
          local_48 = (double)(int)local_c * 0.5;
          do {
            local_34 = (double)(int)local_8 * 0.125 + local_48;
            puVar10 = (undefined1 *)((int)pfVar9 + -4);
            *(undefined4 *)((int)pfVar9 + -4) = 0x5a343f;
            __CIexp();
            *(undefined4 *)(puVar10 + -4) = 0x5a3447;
            _ftol2_sse();
            pfVar9 = (float *)(puVar10 + -4);
            *(undefined4 *)(puVar10 + -4) = 0x5a3463;
            __CIexp();
            *(undefined4 *)((int)pfVar9 + -4) = 0x5a3471;
            _ftol2_sse();
            dVar2 = local_34;
            local_34 = (double)CONCAT44(extraout_EAX_03,(undefined4)local_34);
            fVar18 = extraout_EAX_02;
            if ((int)extraout_EAX_02 < 0) {
              fVar18 = 0.0;
            }
            if ((int)param_2 < (int)fVar18) {
              fVar18 = param_2;
            }
            if ((int)fVar18 < (int)fVar14) {
              fVar14 = fVar18;
            }
            fVar18 = extraout_EAX_03;
            if ((int)extraout_EAX_03 < 0) {
              fVar18 = 0.0;
              local_34 = (double)((ulonglong)dVar2 & 0xffffffff);
            }
            if ((int)param_2 < (int)fVar18) {
              local_34 = (double)CONCAT44(param_2,(undefined4)local_34);
              fVar18 = param_2;
            }
            if ((int)fVar14 < (int)fVar18) {
              if (3 < (int)fVar18 - (int)fVar14) {
                iVar3 = (int)fVar14 + 2;
                pfVar5 = (float *)(local_1c + iVar3);
                do {
                  if ((int)param_2 <= (int)fVar14) goto LAB_005a359b;
                  pfVar4 = local_7f34 + (int)local_28 + (int)local_8;
                  if (local_7f34[(int)local_28 + (int)local_8] < pfVar5[-2]) {
                    pfVar5[-2] = *pfVar4;
                  }
                  if ((int)param_2 <= iVar3 + -1) {
                    fVar14 = (float)((int)fVar14 + 1);
                    goto LAB_005a359b;
                  }
                  if (*pfVar4 < pfVar5[-1]) {
                    pfVar5[-1] = *pfVar4;
                  }
                  if ((int)param_2 <= iVar3) {
                    fVar14 = (float)((int)fVar14 + 2);
                    goto LAB_005a359b;
                  }
                  if (*pfVar4 < *pfVar5) {
                    *pfVar5 = *pfVar4;
                  }
                  if ((int)param_2 <= iVar3 + 1) {
                    fVar14 = (float)((int)fVar14 + 3);
                    goto LAB_005a359b;
                  }
                  if (*pfVar4 < pfVar5[1]) {
                    pfVar5[1] = *pfVar4;
                  }
                  fVar14 = (float)((int)fVar14 + 4);
                  pfVar5 = pfVar5 + 4;
                  iVar3 = iVar3 + 4;
                  fVar18 = local_34._4_4_;
                } while ((int)fVar14 < (int)local_34._4_4_ + -3);
              }
              for (; ((int)fVar14 < (int)fVar18 && ((int)fVar14 < (int)param_2));
                  fVar14 = (float)((int)fVar14 + 1)) {
                if (local_7f34[(int)local_8 + (int)local_28] < (float)local_1c[(int)fVar14]) {
                  local_1c[(int)fVar14] = local_7f34[(int)local_8 + (int)local_28];
                }
              }
            }
LAB_005a359b:
            local_8 = (float)((int)local_8 + 1);
          } while ((int)local_8 < 0x38);
          if ((int)fVar14 < (int)param_2) {
            if (3 < (int)param_2 - (int)fVar14) {
              iVar3 = (((int)param_2 - (int)fVar14) - 4U >> 2) + 1;
              pfVar5 = (float *)(local_1c + (int)fVar14 + 2);
              fVar14 = (float)((int)fVar14 + iVar3 * 4);
              do {
                if (*local_20 < pfVar5[-2]) {
                  pfVar5[-2] = *local_20;
                }
                if (*local_20 < pfVar5[-1]) {
                  pfVar5[-1] = *local_20;
                }
                if (*local_20 < *pfVar5) {
                  *pfVar5 = *local_20;
                }
                if (*local_20 < pfVar5[1]) {
                  pfVar5[1] = *local_20;
                }
                pfVar5 = pfVar5 + 4;
                iVar3 = iVar3 + -1;
              } while (iVar3 != 0);
            }
            for (; (int)fVar14 < (int)param_2; fVar14 = (float)((int)fVar14 + 1)) {
              if (*local_20 < (float)local_1c[(int)fVar14]) {
                local_1c[(int)fVar14] = *local_20;
              }
            }
          }
          local_28 = local_28 + 0x70;
          local_20 = local_20 + 0x1c0;
          local_c = (float *)((int)local_c + 1);
        } while ((int)local_c <= (int)local_24);
      }
      if ((int)local_18 < 0x11) {
        fVar14 = 0.0;
        local_8 = 0.0;
        do {
          local_48 = (double)(int)local_8 * 0.125 + local_40;
          puVar11 = (undefined1 *)((int)pfVar9 + -4);
          *(undefined4 *)((int)pfVar9 + -4) = 0x5a36c6;
          __CIexp();
          *(undefined4 *)(puVar11 + -4) = 0x5a36ce;
          _ftol2_sse();
          pfVar9 = (float *)(puVar11 + -4);
          *(undefined4 *)(puVar11 + -4) = 0x5a36ea;
          __CIexp();
          *(undefined4 *)((int)pfVar9 + -4) = 0x5a36f8;
          _ftol2_sse();
          local_c = extraout_EAX_05;
          fVar18 = extraout_EAX_04;
          if ((int)extraout_EAX_04 < 0) {
            fVar18 = 0.0;
          }
          if ((int)param_2 < (int)fVar18) {
            fVar18 = param_2;
          }
          if ((int)fVar18 < (int)fVar14) {
            fVar14 = fVar18;
          }
          if ((int)extraout_EAX_05 < 0) {
            local_c = (float *)0x0;
          }
          if ((int)param_2 < (int)local_c) {
            local_c = (float *)param_2;
          }
          if ((int)fVar14 < (int)local_c) {
            if (3 < (int)local_c - (int)fVar14) {
              iVar3 = (int)fVar14 + 2;
              pfVar5 = (float *)(local_1c + iVar3);
              do {
                if ((int)param_2 <= (int)fVar14) goto LAB_005a3841;
                iVar15 = (int)local_8 + (local_2c + (int)local_18 * 8) * 0x38;
                pfVar4 = local_7f34 + iVar15;
                if (local_7f34[iVar15] < pfVar5[-2]) {
                  pfVar5[-2] = *pfVar4;
                }
                if ((int)param_2 <= iVar3 + -1) {
                  fVar14 = (float)((int)fVar14 + 1);
                  goto LAB_005a3841;
                }
                if (*pfVar4 < pfVar5[-1]) {
                  pfVar5[-1] = *pfVar4;
                }
                if ((int)param_2 <= iVar3) {
                  fVar14 = (float)((int)fVar14 + 2);
                  goto LAB_005a3841;
                }
                if (*pfVar4 < *pfVar5) {
                  *pfVar5 = *pfVar4;
                }
                if ((int)param_2 <= iVar3 + 1) {
                  fVar14 = (float)((int)fVar14 + 3);
                  goto LAB_005a3841;
                }
                if (*pfVar4 < pfVar5[1]) {
                  pfVar5[1] = *pfVar4;
                }
                fVar14 = (float)((int)fVar14 + 4);
                pfVar5 = pfVar5 + 4;
                iVar3 = iVar3 + 4;
              } while ((int)fVar14 < (int)local_c + -3);
            }
            for (; ((int)fVar14 < (int)local_c && ((int)fVar14 < (int)param_2));
                fVar14 = (float)((int)fVar14 + 1)) {
              if (local_7f34[(int)local_8 + (local_2c + (int)local_18 * 8) * 0x38] <
                  (float)local_1c[(int)fVar14]) {
                local_1c[(int)fVar14] =
                     local_7f34[(int)local_8 + (local_2c + (int)local_18 * 8) * 0x38];
              }
            }
          }
LAB_005a3841:
          local_8 = (float)((int)local_8 + 1);
        } while ((int)local_8 < 0x38);
        if ((int)fVar14 < (int)param_2) {
          if (3 < (int)param_2 - (int)fVar14) {
            iVar3 = (((int)param_2 - (int)fVar14) - 4U >> 2) + 1;
            pfVar5 = (float *)(local_1c + (int)fVar14 + 2);
            pfVar4 = afStack_7e58 + (local_2c + (int)local_18 * 8) * 0x38;
            fVar14 = (float)((int)fVar14 + iVar3 * 4);
            do {
              if (*pfVar4 < pfVar5[-2]) {
                pfVar5[-2] = *pfVar4;
              }
              if (*pfVar4 < pfVar5[-1]) {
                pfVar5[-1] = *pfVar4;
              }
              if (*pfVar4 < *pfVar5) {
                *pfVar5 = *pfVar4;
              }
              if (*pfVar4 < pfVar5[1]) {
                pfVar5[1] = *pfVar4;
              }
              pfVar5 = pfVar5 + 4;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
          }
          if ((int)fVar14 < (int)param_2) {
            do {
              if (afStack_7e58[(local_2c + (int)local_18 * 8) * 0x38] < (float)local_1c[(int)fVar14]
                 ) {
                local_1c[(int)fVar14] = afStack_7e58[(local_2c + (int)local_18 * 8) * 0x38];
              }
              fVar14 = (float)((int)fVar14 + 1);
            } while ((int)fVar14 < (int)param_2);
          }
        }
      }
      puVar17 = local_1c;
      local_8 = 0.0;
      pfVar5 = local_14 + 2;
      do {
        fVar14 = local_8;
        puVar12 = (undefined4 *)((int)pfVar9 + -4);
        pfVar9 = (float *)((int)pfVar9 + -4);
        *puVar12 = 0x5a3973;
        __CIexp();
        *(undefined4 *)((int)pfVar9 + -4) = 0x5a397b;
        _ftol2_sse();
        if (extraout_EAX_06 < 0) {
          fVar18 = -999.0;
        }
        else if (extraout_EAX_06 < (int)param_2) {
          fVar18 = (float)puVar17[extraout_EAX_06];
        }
        else {
          fVar18 = -999.0;
        }
        local_8 = (float)((int)fVar14 + 1);
        *pfVar5 = fVar18;
        pfVar5 = pfVar5 + 1;
      } while ((int)local_8 < 0x38);
      iVar3 = 0;
      pfVar5 = local_4c[local_2c] + 3;
      do {
        if (-200.0 < pfVar5[-1]) break;
        if (-200.0 < *pfVar5) {
          iVar3 = iVar3 + 1;
          break;
        }
        if (-200.0 < pfVar5[1]) {
          iVar3 = iVar3 + 2;
          break;
        }
        if (-200.0 < pfVar5[2]) {
          iVar3 = iVar3 + 3;
          break;
        }
        iVar3 = iVar3 + 4;
        pfVar5 = pfVar5 + 4;
      } while (iVar3 < 0x10);
      local_8 = 7.70714e-44;
      pfVar5 = local_54[local_2c] + 0x38;
      *local_14 = (float)iVar3;
      do {
        if (-200.0 < pfVar5[1]) break;
        if (-200.0 < *pfVar5) {
          local_8 = (float)((int)local_8 + -1);
          break;
        }
        local_8 = (float)((int)local_8 + -2);
        pfVar5 = pfVar5 + -2;
      } while (0x11 < (int)local_8);
      local_2c = local_2c + 1;
      local_14[1] = (float)(int)local_8;
    } while (local_2c < 8);
    local_14 = local_18;
    if (0x10 < (int)local_18) {
      return local_38;
    }
  } while( true );
}
