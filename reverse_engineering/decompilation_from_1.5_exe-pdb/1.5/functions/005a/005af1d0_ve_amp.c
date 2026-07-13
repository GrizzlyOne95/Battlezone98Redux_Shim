/*
 * Entry: 005af1d0
 * Name: _ve_amp
 * Namespace: Global
 * Signature: int _ve_amp(envelope_lookup * param_1, vorbis_info_psy_global * param_2, float * param_3, envelope_band * param_4, envelope_filter_state * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Removing unreachable block (ram,0x005af3fb) */
/* WARNING: Removing unreachable block (ram,0x005af46c) */
/* WARNING: Type propagation algorithm not settling */

int __cdecl
_ve_amp(envelope_lookup *param_1,vorbis_info_psy_global *param_2,float *param_3,
       envelope_band *param_4,envelope_filter_state *param_5)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  int in_EAX;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  int aiStack_4c [4];
  float *local_28;
  int *local_24;
  int local_20;
  uint local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_8;
  
  fVar1 = *(float *)(in_EAX + 0xc);
  iVar13 = *(int *)(in_EAX + 4);
  local_1c = 0;
  aiStack_4c[3] = 0x5af1fd;
  iVar3 = iVar13 * -4;
  iVar5 = *(int *)(in_EAX + 0x9c) / 2;
  local_18 = 2;
  if (1 < iVar5) {
    local_18 = iVar5;
  }
  local_14 = (float)param_1->band[1].end - (float)(iVar5 + -2);
  if (local_14 < 0.0) {
    local_14 = 0.0;
  }
  if ((float)param_1->band[1].end < local_14) {
    local_14 = (float)param_1->band[1].end;
  }
  fVar4 = local_14;
  iVar5 = 0;
  if (3 < iVar13) {
    iVar10 = (iVar13 - 4U >> 2) + 1;
    iVar5 = iVar10 * 4;
    pfVar6 = (float *)(&stack0xffffffc8 + iVar3);
    pfVar7 = param_2->preecho_thresh + 2;
    do {
      pfVar6[-1] = *(float *)((int)pfVar6 +
                             *(int *)(in_EAX + 0x24) + -(int)(&stack0xffffffc4 + iVar3) + -4) *
                   (float)((vorbis_info_psy_global *)(pfVar7 + -3))->eighth_octave_lines;
      *pfVar6 = *(float *)((int)pfVar6 + *(int *)(in_EAX + 0x24) + -(int)(&stack0xffffffc4 + iVar3))
                * *(float *)(((int)param_2 - (int)(&stack0xffffffc4 + iVar3)) + (int)pfVar6);
      iVar10 = iVar10 + -1;
      pfVar6[1] = *(float *)((int)pfVar6 +
                            *(int *)(in_EAX + 0x24) + (4 - (int)(&stack0xffffffc4 + iVar3))) *
                  pfVar7[-1];
      pfVar6[2] = *(float *)((int)pfVar6 +
                            *(int *)(in_EAX + 0x24) + (8 - (int)(&stack0xffffffc4 + iVar3))) *
                  *pfVar7;
      pfVar6 = pfVar6 + 4;
      pfVar7 = pfVar7 + 4;
    } while (iVar10 != 0);
  }
  if (iVar5 < iVar13) {
    pfVar6 = (float *)(&stack0xffffffc4 + iVar5 * 4 + iVar3);
    do {
      iVar10 = iVar5 * 4;
      iVar5 = iVar5 + 1;
      *pfVar6 = *(float *)(*(int *)(in_EAX + 0x24) + iVar10) *
                *(float *)((int)pfVar6 + ((int)param_2 - (int)(&stack0xffffffc4 + iVar3)));
      pfVar6 = pfVar6 + 1;
    } while (iVar5 < iVar13);
  }
  aiStack_4c[3 - iVar13] = (int)(&stack0xffffffc4 + iVar3);
  aiStack_4c[2 - iVar13] = (int)(&stack0xffffffc4 + iVar3);
  aiStack_4c[1 - iVar13] = in_EAX + 0x10;
  aiStack_4c[-iVar13] = 0x5af326;
  mdct_forward((mdct_lookup *)aiStack_4c[1 - iVar13],(float *)aiStack_4c[2 - iVar13],
               (float *)aiStack_4c[3 - iVar13]);
  fVar2 = param_4[8].total;
  pfVar6 = (float *)(*(float *)(&stack0xffffffcc + iVar3) * 0.2 *
                     *(float *)(&stack0xffffffcc + iVar3) +
                    *(float *)(&stack0xffffffc8 + iVar3) * 0.7 *
                    *(float *)(&stack0xffffffc8 + iVar3) +
                    *(float *)(&stack0xffffffc4 + iVar3) * *(float *)(&stack0xffffffc4 + iVar3));
  if (fVar2 == 0.0) {
    local_8 = (float)pfVar6 + (float)param_4[8].window;
    param_4[8].end = (int)local_8;
    param_4[8].window = pfVar6;
  }
  else {
    local_8 = (float)pfVar6 + (float)param_4[8].end;
    param_4[8].end = (int)local_8;
    param_4[8].window = (float *)((float)pfVar6 + (float)param_4[8].window);
  }
  param_4[8].end = (int)((float)param_4[8].end - (float)(&param_4[4].window)[(int)fVar2]);
  (&param_4[4].window)[(int)fVar2] = pfVar6;
  param_4[8].total = (float)((int)param_4[8].total + 1);
  if (0xe < (int)param_4[8].total) {
    param_4[8].total = 0.0;
  }
  iVar5 = 0;
  local_8 = ((float)(int)ABS(local_8 * 0.0625) * 7.1771143e-07 - 764.6162) * 0.5 - 15.0;
  if (0 < iVar13 / 2) {
    do {
      local_10 = ((float)(int)ABS(*(float *)(&stack0xffffffc4 + iVar5 * 4 + iVar3) *
                                  *(float *)(&stack0xffffffc4 + iVar5 * 4 + iVar3) +
                                  *(float *)(&stack0xffffffc8 + iVar5 * 4 + iVar3) *
                                  *(float *)(&stack0xffffffc8 + iVar5 * 4 + iVar3)) * 7.1771143e-07
                 - 764.6162) * 0.5;
      if (local_10 < local_8) {
        local_10 = local_8;
      }
      if (local_10 < fVar1) {
        local_10 = fVar1;
      }
      *(float *)(&stack0xffffffc4 + (iVar5 >> 1) * 4 + iVar3) = local_10;
      iVar5 = iVar5 + 2;
      local_8 = local_8 - 8.0;
    } while (iVar5 < iVar13 / 2);
  }
  local_28 = &(param_1->mdct).scale;
  local_24 = &param_4[4].end;
  local_20 = 0;
  pfVar6 = param_3 + 2;
  do {
    fVar1 = pfVar6[-1];
    iVar13 = 0;
    local_10 = 0.0;
    if (3 < (int)fVar1) {
      iVar5 = ((int)fVar1 - 4U >> 2) + 1;
      iVar13 = iVar5 * 4;
      pfVar7 = (float *)((int)*pfVar6 + 8);
      pfVar8 = (float *)(&stack0xffffffcc + (int)pfVar6[-2] * 4 + iVar3);
      do {
        iVar5 = iVar5 + -1;
        local_10 = pfVar8[1] * pfVar7[1] +
                   *pfVar7 * *pfVar8 + pfVar8[-1] * pfVar7[-1] + pfVar8[-2] * pfVar7[-2] + local_10;
        pfVar7 = pfVar7 + 4;
        pfVar8 = pfVar8 + 4;
      } while (iVar5 != 0);
    }
    if (iVar13 < (int)fVar1) {
      pfVar7 = (float *)(&stack0xffffffc4 + ((int)pfVar6[-2] + iVar13) * 4 + iVar3);
      iVar5 = (int)fVar1 - iVar13;
      pfVar8 = (float *)((int)*pfVar6 + iVar13 * 4);
      do {
        fVar1 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        iVar5 = iVar5 + -1;
        local_10 = fVar1 * *pfVar8 + local_10;
        pfVar8 = pfVar8 + 1;
      } while (iVar5 != 0);
    }
    fVar1 = pfVar6[1] * local_10;
    iVar13 = *local_24 + -1;
    local_8 = -99999.0;
    param_1 = (envelope_lookup *)0x47c34f80;
    if (iVar13 < 0) {
      iVar13 = *local_24 + 0x10;
    }
    piVar11 = &param_4->begin + local_20 + iVar13;
    local_10 = fVar1;
    if (fVar1 <= (float)(&param_4->begin)[local_20 + iVar13]) {
      local_10 = (float)*piVar11;
    }
    local_14 = fVar1;
    if ((float)*piVar11 <= fVar1) {
      local_14 = (float)*piVar11;
    }
    iVar5 = 0;
    if (3 < local_18) {
      iVar10 = (local_18 - 4U >> 2) + 1;
      iVar5 = iVar10 * 4;
      do {
        iVar9 = iVar13 + -1;
        pfVar7 = (float *)(piVar11 + -1);
        if (iVar9 < 0) {
          iVar9 = iVar13 + 0x10;
          pfVar7 = (float *)(piVar11 + 0x10);
        }
        if (local_8 <= *pfVar7) {
          local_8 = *pfVar7;
        }
        if (*pfVar7 <= (float)param_1) {
          param_1 = (envelope_lookup *)*pfVar7;
        }
        iVar13 = iVar9 + -1;
        pfVar8 = pfVar7 + -1;
        if (iVar13 < 0) {
          iVar13 = iVar9 + 0x10;
          pfVar8 = pfVar7 + 0x10;
        }
        if (local_8 <= *pfVar8) {
          local_8 = *pfVar8;
        }
        if (*pfVar8 <= (float)param_1) {
          param_1 = (envelope_lookup *)*pfVar8;
        }
        iVar9 = iVar13 + -1;
        pfVar7 = pfVar8 + -1;
        if (iVar9 < 0) {
          iVar9 = iVar13 + 0x10;
          pfVar7 = pfVar8 + 0x10;
        }
        if (local_8 <= *pfVar7) {
          local_8 = *pfVar7;
        }
        if (*pfVar7 <= (float)param_1) {
          param_1 = (envelope_lookup *)*pfVar7;
        }
        iVar13 = iVar9 + -1;
        piVar11 = (int *)(pfVar7 + -1);
        if (iVar13 < 0) {
          iVar13 = iVar9 + 0x10;
          piVar11 = (int *)(pfVar7 + 0x10);
        }
        if (local_8 <= (float)*piVar11) {
          local_8 = (float)*piVar11;
        }
        if ((float)*piVar11 <= (float)param_1) {
          param_1 = (envelope_lookup *)*piVar11;
        }
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    if (iVar5 < local_18) {
      iVar5 = local_18 - iVar5;
      piVar11 = &param_4->begin + local_20 + iVar13;
      do {
        iVar10 = iVar13 + -1;
        piVar12 = piVar11 + -1;
        if (iVar10 < 0) {
          iVar10 = iVar13 + 0x10;
          piVar12 = piVar11 + 0x10;
        }
        if (local_8 <= (float)*piVar12) {
          local_8 = (float)*piVar12;
        }
        if ((float)*piVar12 <= (float)param_1) {
          param_1 = (envelope_lookup *)*piVar12;
        }
        iVar5 = iVar5 + -1;
        iVar13 = iVar10;
        piVar11 = piVar12;
      } while (iVar5 != 0);
    }
    (&param_4->begin)[*local_24 + local_20] = (int)fVar1;
    *local_24 = *local_24 + 1;
    if (0x10 < *local_24) {
      *local_24 = 0;
    }
    if (local_28[-7] + fVar4 < local_10 - local_8) {
      local_1c = local_1c | 5;
    }
    if (local_14 - (float)param_1 < *local_28 - fVar4) {
      local_1c = local_1c | 2;
    }
    local_20 = local_20 + 0x24;
    local_24 = local_24 + 0x24;
    local_28 = local_28 + 1;
    pfVar6 = pfVar6 + 4;
  } while (local_20 < 0xfc);
  return local_1c;
}
