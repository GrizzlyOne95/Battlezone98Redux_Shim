/*
 * Entry: 005b05d0
 * Name: mapping0_forward
 * Namespace: Global
 * Signature: int mapping0_forward(vorbis_block * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Removing unreachable block (ram,0x005b0a30) */
/* WARNING: Removing unreachable block (ram,0x005b09d6) */
/* WARNING: Removing unreachable block (ram,0x005b0813) */
/* WARNING: Removing unreachable block (ram,0x005b06c7) */
/* WARNING: Removing unreachable block (ram,0x005b0799) */
/* WARNING: Removing unreachable block (ram,0x005b09a5) */
/* WARNING: Removing unreachable block (ram,0x005b0a03) */
/* WARNING: Removing unreachable block (ram,0x005b0a8b) */

int __cdecl mapping0_forward(vorbis_block *param_1)

{
  uint uVar1;
  vorbis_info *pvVar2;
  void *pvVar3;
  void *pvVar4;
  void *pvVar5;
  int iVar6;
  int *piVar7;
  float *pfVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  int iVar12;
  code *pcVar13;
  int iVar14;
  int iVar15;
  float fVar16;
  float fVar17;
  vorbis_block *pvVar18;
  void *pvVar19;
  undefined4 *puVar20;
  int *piVar21;
  int iVar22;
  void *pvVar23;
  int iVar24;
  void *pvVar25;
  void *pvVar26;
  float *pfVar27;
  int *piVar28;
  int iVar29;
  undefined4 uVar30;
  int iVar31;
  undefined4 *puVar32;
  int iVar33;
  uint *puVar34;
  int iVar35;
  float *pfVar36;
  undefined1 *puVar37;
  undefined4 *puVar38;
  undefined4 *puVar39;
  undefined1 *puVar40;
  int *piVar41;
  int aiStack_c4 [12];
  long alStack_94 [3];
  int aiStack_88 [2];
  float afStack_80 [2];
  undefined4 *local_64;
  int local_5c;
  int *local_50;
  int local_4c;
  float local_3c;
  int *local_38;
  float *local_34;
  undefined4 *local_30;
  int local_24;
  int local_1c;
  
  pvVar18 = param_1;
  pvVar2 = param_1->vd->vi;
  pvVar3 = param_1->vd->backend_state;
  pvVar4 = pvVar2->codec_setup;
  pvVar5 = param_1->internal;
  iVar29 = pvVar2->channels;
  iVar24 = param_1->pcmend;
  afStack_80[1] = 8.359198e-39;
  iVar14 = iVar29 * -4;
  afStack_80[1 - iVar29] = (float)(iVar29 * 4);
  afStack_80[-iVar29] = (float)param_1;
  aiStack_88[1 - iVar29] = 0x5b0615;
  pvVar19 = _vorbis_block_alloc((vorbis_block *)afStack_80[-iVar29],(long)afStack_80[1 - iVar29]);
  aiStack_88[1 - iVar29] = pvVar2->channels * 4;
  aiStack_88[-iVar29] = (int)param_1;
  alStack_94[2 - iVar29] = 0x5b0626;
  puVar20 = _vorbis_block_alloc((vorbis_block *)aiStack_88[-iVar29],aiStack_88[1 - iVar29]);
  alStack_94[2 - iVar29] = pvVar2->channels * 4;
  alStack_94[1 - iVar29] = (long)param_1;
  alStack_94[-iVar29] = 0x5b0637;
  piVar21 = _vorbis_block_alloc((vorbis_block *)alStack_94[1 - iVar29],alStack_94[2 - iVar29]);
  local_3c = *(float *)((int)pvVar5 + 4);
  iVar31 = pvVar2->channels;
  afStack_80[1 - iVar29] = 8.359297e-39;
  iVar15 = iVar31 * -4;
  local_34 = (float *)(&stack0xffffff88 + iVar15 + iVar14);
  iVar6 = param_1->W;
  piVar7 = *(int **)((int)pvVar4 + iVar6 * 4 + 0x220);
  iVar22 = ((-(uint)(iVar6 != 0) & 2) + *(int *)((int)pvVar5 + 8)) * 0x34 +
           *(int *)((int)pvVar3 + 0x38);
  param_1->mode = iVar6;
  param_1 = (vorbis_block *)0x0;
  if (0 < pvVar2->channels) {
    iVar12 = (iVar24 / 2) * 4;
    fVar16 = ((float)(int)ABS(4.0 / (float)iVar24) * 7.1771143e-07 - 764.6162) + 0.345;
    do {
      pfVar8 = pvVar18->pcm[(int)param_1];
      afStack_80[(1 - iVar31) - iVar29] = (float)iVar12;
      puVar32 = (undefined4 *)
                (((int)pvVar19 - (int)(&stack0xffffff88 + iVar15 + iVar14)) + (int)local_34);
      afStack_80[-iVar29 - iVar31] = (float)pvVar18;
      aiStack_88[(1 - iVar31) - iVar29] = 0x5b071d;
      pvVar23 = _vorbis_block_alloc((vorbis_block *)afStack_80[-iVar29 - iVar31],
                                    (long)afStack_80[(1 - iVar31) - iVar29]);
      *(void **)((int)puVar32 + ((int)puVar20 - (int)pvVar19)) = pvVar23;
      aiStack_88[(1 - iVar31) - iVar29] = iVar12;
      aiStack_88[-iVar29 - iVar31] = (int)pvVar18;
      alStack_94[(2 - iVar31) - iVar29] = 0x5b0730;
      pvVar23 = _vorbis_block_alloc((vorbis_block *)aiStack_88[-iVar29 - iVar31],
                                    aiStack_88[(1 - iVar31) - iVar29]);
      *puVar32 = pvVar23;
      lVar9 = pvVar18->W;
      lVar10 = pvVar18->lW;
      alStack_94[(2 - iVar31) - iVar29] = pvVar18->nW;
      alStack_94[(1 - iVar31) - iVar29] = lVar9;
      alStack_94[-iVar29 - iVar31] = lVar10;
      aiStack_c4[(0xb - iVar31) - iVar29] = (int)pvVar4;
      aiStack_c4[(10 - iVar31) - iVar29] = (int)pvVar3 + 4;
      aiStack_c4[(9 - iVar31) - iVar29] = (int)pfVar8;
      aiStack_c4[(8 - iVar31) - iVar29] = 0x5b0752;
      _vorbis_apply_window
                ((float *)aiStack_c4[(9 - iVar31) - iVar29],
                 (int *)aiStack_c4[(10 - iVar31) - iVar29],
                 (long *)aiStack_c4[(0xb - iVar31) - iVar29],alStack_94[-iVar29 - iVar31],
                 alStack_94[(1 - iVar31) - iVar29],alStack_94[(2 - iVar31) - iVar29]);
      iVar33 = pvVar18->W;
      aiStack_c4[(8 - iVar31) - iVar29] = *puVar32;
      uVar11 = **(undefined4 **)((int)pvVar3 + iVar33 * 4 + 0xc);
      aiStack_c4[(7 - iVar31) - iVar29] = (int)pfVar8;
      aiStack_c4[(6 - iVar31) - iVar29] = uVar11;
      aiStack_c4[(5 - iVar31) - iVar29] = 0x5b076b;
      mdct_forward((mdct_lookup *)aiStack_c4[(6 - iVar31) - iVar29],
                   (float *)aiStack_c4[(7 - iVar31) - iVar29],
                   (float *)aiStack_c4[(8 - iVar31) - iVar29]);
      iVar33 = pvVar18->W;
      aiStack_c4[(5 - iVar31) - iVar29] = (int)pfVar8;
      aiStack_c4[(4 - iVar31) - iVar29] = (int)pvVar3 + iVar33 * 0xc + 0x14;
      aiStack_c4[(3 - iVar31) - iVar29] = 0x5b077f;
      drft_forward((drft_lookup *)aiStack_c4[(4 - iVar31) - iVar29],
                   (float *)aiStack_c4[(5 - iVar31) - iVar29]);
      iVar33 = 1;
      fVar17 = fVar16 + ((float)(int)ABS(*pfVar8) * 7.1771143e-07 - 764.6162) + 0.345;
      *pfVar8 = fVar17;
      *local_34 = fVar17;
      if (1 < iVar24 + -1) {
        do {
          fVar17 = ((float)(int)ABS(pfVar8[iVar33] * pfVar8[iVar33] +
                                    pfVar8[iVar33 + 1] * pfVar8[iVar33 + 1]) * 7.1771143e-07 -
                   764.6162) * 0.5 + fVar16 + 0.345;
          pfVar8[iVar33 + 1 >> 1] = fVar17;
          if (*local_34 < fVar17) {
            *local_34 = fVar17;
          }
          iVar33 = iVar33 + 2;
        } while (iVar33 < iVar24 + -1);
      }
      if (0.0 < *local_34) {
        *local_34 = 0.0;
      }
      if (local_3c < *local_34) {
        local_3c = *local_34;
      }
      param_1 = (vorbis_block *)((int)&param_1->pcm + 1);
      local_34 = local_34 + 1;
    } while ((int)param_1 < pvVar2->channels);
  }
  iVar24 = iVar24 / 2;
  afStack_80[(1 - iVar31) - iVar29] = (float)(iVar24 * 4);
  afStack_80[-iVar29 - iVar31] = (float)pvVar18;
  aiStack_88[(1 - iVar31) - iVar29] = 0x5b08b9;
  pvVar23 = _vorbis_block_alloc((vorbis_block *)afStack_80[-iVar29 - iVar31],
                                (long)afStack_80[(1 - iVar31) - iVar29]);
  aiStack_88[(1 - iVar31) - iVar29] = iVar24 * 4;
  aiStack_88[-iVar29 - iVar31] = (int)pvVar18;
  alStack_94[(2 - iVar31) - iVar29] = 0x5b08c3;
  pvVar25 = _vorbis_block_alloc((vorbis_block *)aiStack_88[-iVar29 - iVar31],
                                aiStack_88[(1 - iVar31) - iVar29]);
  param_1 = (vorbis_block *)0x0;
  if (0 < pvVar2->channels) {
    piVar41 = piVar21;
    local_50 = piVar7;
    do {
      local_50 = local_50 + 1;
      iVar12 = *local_50;
      iVar33 = *(int *)((int)pvVar19 +
                       (int)piVar41 +
                       ((int)(&stack0xffffff88 + ((iVar15 + iVar14) - (int)piVar21)) -
                       (int)(&stack0xffffff88 + iVar15 + iVar14)));
      pfVar8 = pvVar18->pcm[(int)param_1];
      pfVar36 = pfVar8 + iVar24;
      afStack_80[(1 - iVar31) - iVar29] = 8.40779e-44;
      afStack_80[-iVar29 - iVar31] = (float)pvVar18;
      pvVar18->mode = iVar6;
      aiStack_88[(1 - iVar31) - iVar29] = 0x5b0938;
      pvVar26 = _vorbis_block_alloc((vorbis_block *)afStack_80[-iVar29 - iVar31],
                                    (long)afStack_80[(1 - iVar31) - iVar29]);
      aiStack_88[(1 - iVar31) - iVar29] = 0x3c;
      aiStack_88[-iVar29 - iVar31] = 0;
      alStack_94[(2 - iVar31) - iVar29] = (long)pvVar26;
      *piVar41 = (int)pvVar26;
      alStack_94[(1 - iVar31) - iVar29] = 0x5b0944;
      memset();
      local_1c = 0;
      if (3 < iVar24) {
        puVar34 = (uint *)(iVar33 + 0xc);
        local_5c = (iVar24 - 4U >> 2) + 1;
        local_1c = local_5c * 4;
        pfVar27 = pfVar36 + 1;
        do {
          pfVar27[-1] = ((float)(puVar34[-3] & 0x7fffffff) * 7.1771143e-07 - 764.6162) + 0.345;
          *pfVar27 = ((float)(*(uint *)((iVar33 - (int)pfVar36) + (int)pfVar27) & 0x7fffffff) *
                      7.1771143e-07 - 764.6162) + 0.345;
          pfVar27[1] = ((float)(puVar34[-1] & 0x7fffffff) * 7.1771143e-07 - 764.6162) + 0.345;
          uVar1 = *puVar34;
          puVar34 = puVar34 + 4;
          local_5c = local_5c + -1;
          pfVar27[2] = ((float)(uVar1 & 0x7fffffff) * 7.1771143e-07 - 764.6162) + 0.345;
          pfVar27 = pfVar27 + 4;
        } while (local_5c != 0);
      }
      if (local_1c < iVar24) {
        iVar35 = iVar24 - local_1c;
        pfVar27 = pfVar36 + local_1c;
        do {
          iVar35 = iVar35 + -1;
          *pfVar27 = ((float)(*(uint *)((int)pfVar27 + (iVar33 - (int)pfVar36)) & 0x7fffffff) *
                      7.1771143e-07 - 764.6162) + 0.345;
          pfVar27 = pfVar27 + 1;
        } while (iVar35 != 0);
      }
      afStack_80[(1 - iVar31) - iVar29] = (float)pvVar23;
      afStack_80[-iVar29 - iVar31] = (float)pfVar36;
      aiStack_88[(1 - iVar31) - iVar29] = iVar22;
      aiStack_88[-iVar29 - iVar31] = 0x5b0abc;
      _vp_noisemask((vorbis_look_psy *)aiStack_88[(1 - iVar31) - iVar29],
                    (float *)afStack_80[-iVar29 - iVar31],(float *)afStack_80[(1 - iVar31) - iVar29]
                   );
      afStack_80[(1 - iVar31) - iVar29] =
           *(float *)((int)piVar41 + (int)(&stack0xffffff88 + ((iVar15 + iVar14) - (int)piVar21)));
      afStack_80[-iVar29 - iVar31] = local_3c;
      aiStack_88[(1 - iVar31) - iVar29] = (int)pvVar25;
      aiStack_88[-iVar29 - iVar31] = (int)pfVar8;
      alStack_94[(2 - iVar31) - iVar29] = iVar22;
      alStack_94[(1 - iVar31) - iVar29] = 0x5b0ae4;
      _vp_tonemask((vorbis_look_psy *)alStack_94[(2 - iVar31) - iVar29],
                   (float *)aiStack_88[-iVar29 - iVar31],(float *)aiStack_88[(1 - iVar31) - iVar29],
                   afStack_80[-iVar29 - iVar31],afStack_80[(1 - iVar31) - iVar29]);
      alStack_94[(1 - iVar31) - iVar29] = (long)pfVar36;
      alStack_94[-iVar29 - iVar31] = iVar33;
      aiStack_c4[(0xb - iVar31) - iVar29] = (int)pfVar8;
      aiStack_c4[(10 - iVar31) - iVar29] = 1;
      aiStack_c4[(9 - iVar31) - iVar29] = (int)pvVar25;
      aiStack_c4[(8 - iVar31) - iVar29] = (int)pvVar23;
      aiStack_c4[(7 - iVar31) - iVar29] = iVar22;
      aiStack_c4[(6 - iVar31) - iVar29] = 0x5b0b00;
      _vp_offset_and_mix((vorbis_look_psy *)aiStack_c4[(7 - iVar31) - iVar29],
                         (float *)aiStack_c4[(8 - iVar31) - iVar29],
                         (float *)aiStack_c4[(9 - iVar31) - iVar29],
                         aiStack_c4[(10 - iVar31) - iVar29],
                         (float *)aiStack_c4[(0xb - iVar31) - iVar29],
                         (float *)alStack_94[-iVar29 - iVar31],
                         (float *)alStack_94[(1 - iVar31) - iVar29]);
      iVar35 = piVar7[iVar12 + 0x101];
      if (*(int *)((int)pvVar4 + iVar35 * 4 + 800) != 1) {
        return -1;
      }
      afStack_80[(1 - iVar31) - iVar29] = (float)pfVar8;
      uVar11 = *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + iVar35 * 4);
      afStack_80[-iVar29 - iVar31] = (float)pfVar36;
      aiStack_88[(1 - iVar31) - iVar29] = uVar11;
      aiStack_88[-iVar29 - iVar31] = (int)pvVar18;
      alStack_94[(2 - iVar31) - iVar29] = 0x5b0b36;
      piVar28 = floor1_fit((vorbis_block *)aiStack_88[-iVar29 - iVar31],
                           (vorbis_look_floor1 *)aiStack_88[(1 - iVar31) - iVar29],
                           (float *)afStack_80[-iVar29 - iVar31],
                           (float *)afStack_80[(1 - iVar31) - iVar29]);
      iVar35 = *piVar41;
      alStack_94[(2 - iVar31) - iVar29] = (long)pvVar18;
      *(int **)(iVar35 + 0x1c) = piVar28;
      alStack_94[(1 - iVar31) - iVar29] = 0x5b0b41;
      iVar35 = vorbis_bitrate_managed((vorbis_block *)alStack_94[(2 - iVar31) - iVar29]);
      if ((iVar35 != 0) && (*(int *)(*piVar41 + 0x1c) != 0)) {
        afStack_80[(1 - iVar31) - iVar29] = (float)pfVar36;
        afStack_80[-iVar29 - iVar31] = (float)iVar33;
        aiStack_88[(1 - iVar31) - iVar29] = (int)pfVar8;
        aiStack_88[-iVar29 - iVar31] = 2;
        alStack_94[(2 - iVar31) - iVar29] = (long)pvVar25;
        alStack_94[(1 - iVar31) - iVar29] = (long)pvVar23;
        alStack_94[-iVar29 - iVar31] = iVar22;
        aiStack_c4[(0xb - iVar31) - iVar29] = 0x5b0b74;
        _vp_offset_and_mix((vorbis_look_psy *)alStack_94[-iVar29 - iVar31],
                           (float *)alStack_94[(1 - iVar31) - iVar29],
                           (float *)alStack_94[(2 - iVar31) - iVar29],aiStack_88[-iVar29 - iVar31],
                           (float *)aiStack_88[(1 - iVar31) - iVar29],
                           (float *)afStack_80[-iVar29 - iVar31],
                           (float *)afStack_80[(1 - iVar31) - iVar29]);
        aiStack_c4[(0xb - iVar31) - iVar29] = (int)pfVar8;
        uVar11 = *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + piVar7[iVar12 + 0x101] * 4);
        aiStack_c4[(10 - iVar31) - iVar29] = (int)pfVar36;
        aiStack_c4[(9 - iVar31) - iVar29] = uVar11;
        aiStack_c4[(8 - iVar31) - iVar29] = (int)pvVar18;
        aiStack_c4[(7 - iVar31) - iVar29] = 0x5b0b96;
        piVar28 = floor1_fit((vorbis_block *)aiStack_c4[(8 - iVar31) - iVar29],
                             (vorbis_look_floor1 *)aiStack_c4[(9 - iVar31) - iVar29],
                             (float *)aiStack_c4[(10 - iVar31) - iVar29],
                             (float *)aiStack_c4[(0xb - iVar31) - iVar29]);
        iVar35 = *piVar41;
        aiStack_c4[(7 - iVar31) - iVar29] = (int)pfVar36;
        aiStack_c4[(6 - iVar31) - iVar29] = iVar33;
        *(int **)(iVar35 + 0x38) = piVar28;
        aiStack_c4[(5 - iVar31) - iVar29] = (int)pfVar8;
        aiStack_c4[(4 - iVar31) - iVar29] = 0;
        aiStack_c4[(3 - iVar31) - iVar29] = (int)pvVar25;
        aiStack_c4[(2 - iVar31) - iVar29] = (int)pvVar23;
        aiStack_c4[(1 - iVar31) - iVar29] = iVar22;
        aiStack_c4[-iVar29 - iVar31] = 0x5b0bb7;
        _vp_offset_and_mix((vorbis_look_psy *)aiStack_c4[(1 - iVar31) - iVar29],
                           (float *)aiStack_c4[(2 - iVar31) - iVar29],
                           (float *)aiStack_c4[(3 - iVar31) - iVar29],
                           aiStack_c4[(4 - iVar31) - iVar29],
                           (float *)aiStack_c4[(5 - iVar31) - iVar29],
                           (float *)aiStack_c4[(6 - iVar31) - iVar29],
                           (float *)aiStack_c4[(7 - iVar31) - iVar29]);
        afStack_80[(1 - iVar31) - iVar29] = (float)pfVar8;
        uVar11 = *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + piVar7[iVar12 + 0x101] * 4);
        afStack_80[-iVar29 - iVar31] = (float)pfVar36;
        aiStack_88[(1 - iVar31) - iVar29] = uVar11;
        aiStack_88[-iVar29 - iVar31] = (int)pvVar18;
        alStack_94[(2 - iVar31) - iVar29] = 0x5b0bdc;
        piVar28 = floor1_fit((vorbis_block *)aiStack_88[-iVar29 - iVar31],
                             (vorbis_look_floor1 *)aiStack_88[(1 - iVar31) - iVar29],
                             (float *)afStack_80[-iVar29 - iVar31],
                             (float *)afStack_80[(1 - iVar31) - iVar29]);
        *(int **)*piVar41 = piVar28;
        local_5c = 4;
        iVar33 = 0x10000;
        do {
          puVar32 = (undefined4 *)*piVar41;
          uVar11 = puVar32[7];
          afStack_80[(1 - iVar31) - iVar29] = (float)(iVar33 / 7);
          uVar30 = *puVar32;
          afStack_80[-iVar29 - iVar31] = (float)uVar11;
          aiStack_88[(1 - iVar31) - iVar29] = uVar30;
          aiStack_88[-iVar29 - iVar31] =
               *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + piVar7[iVar12 + 0x101] * 4);
          alStack_94[(2 - iVar31) - iVar29] = (long)pvVar18;
          alStack_94[(1 - iVar31) - iVar29] = 0x5b0c2a;
          piVar28 = floor1_interpolate_fit
                              ((vorbis_block *)alStack_94[(2 - iVar31) - iVar29],
                               (vorbis_look_floor1 *)aiStack_88[-iVar29 - iVar31],
                               (int *)aiStack_88[(1 - iVar31) - iVar29],
                               (int *)afStack_80[-iVar29 - iVar31],
                               (int)afStack_80[(1 - iVar31) - iVar29]);
          *(int **)(local_5c + *piVar41) = piVar28;
          iVar33 = iVar33 + 0x10000;
          local_5c = local_5c + 4;
        } while (iVar33 < 0x70000);
        local_5c = 0x20;
        iVar33 = 0x10000;
        do {
          iVar35 = *piVar41;
          uVar11 = *(undefined4 *)(iVar35 + 0x38);
          afStack_80[(1 - iVar31) - iVar29] = (float)(iVar33 / 7);
          uVar30 = *(undefined4 *)(iVar35 + 0x1c);
          afStack_80[-iVar29 - iVar31] = (float)uVar11;
          aiStack_88[(1 - iVar31) - iVar29] = uVar30;
          aiStack_88[-iVar29 - iVar31] =
               *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + piVar7[iVar12 + 0x101] * 4);
          alStack_94[(2 - iVar31) - iVar29] = (long)pvVar18;
          alStack_94[(1 - iVar31) - iVar29] = 0x5b0c90;
          piVar28 = floor1_interpolate_fit
                              ((vorbis_block *)alStack_94[(2 - iVar31) - iVar29],
                               (vorbis_look_floor1 *)aiStack_88[-iVar29 - iVar31],
                               (int *)aiStack_88[(1 - iVar31) - iVar29],
                               (int *)afStack_80[-iVar29 - iVar31],
                               (int)afStack_80[(1 - iVar31) - iVar29]);
          *(int **)(local_5c + *piVar41) = piVar28;
          iVar33 = iVar33 + 0x10000;
          local_5c = local_5c + 4;
        } while (iVar33 < 0x70000);
      }
      param_1 = (vorbis_block *)((int)&param_1->pcm + 1);
      piVar41 = piVar41 + 1;
    } while ((int)param_1 < pvVar2->channels);
  }
  *(float *)((int)pvVar5 + 4) = local_3c;
  iVar24 = pvVar2->channels;
  afStack_80[(1 - iVar31) - iVar29] = 8.361653e-39;
  iVar12 = iVar24 * -4;
  puVar40 = &stack0xffffff88 + iVar24 * -8 + iVar15 + iVar14;
  afStack_80[((1 - iVar24) - iVar31) - iVar29] = 8.361671e-39;
  afStack_80[((iVar24 * -2 + 1) - iVar31) - iVar29] = (float)pvVar18;
  afStack_80[(iVar24 * -2 - iVar31) - iVar29] = 8.361684e-39;
  iVar33 = vorbis_bitrate_managed((vorbis_block *)afStack_80[((iVar24 * -2 + 1) - iVar31) - iVar29])
  ;
  local_24 = (-(uint)(iVar33 != 0) & 0xfffffff9) + 7;
  afStack_80[(iVar24 * -2 - iVar31) - iVar29] = (float)pvVar18;
  afStack_80[((iVar24 * -2 + -1) - iVar31) - iVar29] = 8.36171e-39;
  iVar29 = vorbis_bitrate_managed((vorbis_block *)afStack_80[(iVar24 * -2 - iVar31) - iVar29]);
  if (local_24 <= (int)((-(uint)(iVar29 != 0) & 7) + 7)) {
    local_34 = (float *)(local_24 * 4);
    local_30 = (undefined4 *)((int)pvVar5 + local_24 * 4 + 0xc);
    do {
      uVar11 = *local_30;
      *(undefined4 *)(puVar40 + -4) = 1;
      *(undefined4 *)(puVar40 + -8) = 0;
      *(undefined4 *)(puVar40 + -0xc) = uVar11;
      *(undefined4 *)(puVar40 + -0x10) = 0x5b0d4c;
      oggpack_write();
      *(undefined4 *)(puVar40 + -0x10) = *(undefined4 *)((int)pvVar3 + 0x2c);
      *(int *)(puVar40 + -0x14) = iVar6;
      *(undefined4 *)(puVar40 + -0x18) = uVar11;
      *(undefined4 *)(puVar40 + -0x1c) = 0x5b0d60;
      oggpack_write();
      if (pvVar18->W != 0) {
        lVar9 = pvVar18->lW;
        *(undefined4 *)(puVar40 + -4) = 1;
        *(long *)(puVar40 + -8) = lVar9;
        *(undefined4 *)(puVar40 + -0xc) = uVar11;
        *(undefined4 *)(puVar40 + -0x10) = 0x5b0d78;
        oggpack_write();
        lVar9 = pvVar18->nW;
        *(undefined4 *)(puVar40 + -0x10) = 1;
        *(long *)(puVar40 + -0x14) = lVar9;
        *(undefined4 *)(puVar40 + -0x18) = uVar11;
        *(undefined4 *)(puVar40 + -0x1c) = 0x5b0d87;
        oggpack_write();
      }
      param_1 = (vorbis_block *)0x0;
      if (0 < pvVar2->channels) {
        piVar41 = piVar21;
        local_50 = piVar7;
        do {
          local_50 = local_50 + 1;
          iVar29 = *local_50;
          *(undefined4 *)(puVar40 + -4) =
               *(undefined4 *)(((int)puVar20 - (int)piVar21) + (int)piVar41);
          iVar29 = piVar7[iVar29 + 0x101];
          *(undefined4 *)(puVar40 + -8) = *(undefined4 *)((int)local_34 + *piVar41);
          *(undefined4 *)(puVar40 + -0xc) =
               *(undefined4 *)(*(int *)((int)pvVar3 + 0x30) + iVar29 * 4);
          *(vorbis_block **)(puVar40 + -0x10) = pvVar18;
          *(undefined4 *)(puVar40 + -0x14) = uVar11;
          *(undefined4 *)(puVar40 + -0x18) = 0x5b0e03;
          iVar29 = floor1_encode(*(oggpack_buffer **)(puVar40 + -0x14),
                                 *(vorbis_block **)(puVar40 + -0x10),
                                 *(vorbis_look_floor1 **)(puVar40 + -0xc),*(int **)(puVar40 + -8),
                                 *(int **)(puVar40 + -4));
          *(int *)(&stack0xffffff88 + (iVar14 - (int)piVar21) + (int)piVar41) = iVar29;
          param_1 = (vorbis_block *)((int)&param_1->pcm + 1);
          piVar41 = piVar41 + 1;
        } while ((int)param_1 < pvVar2->channels);
      }
      *(int *)(puVar40 + -4) = pvVar2->channels;
      *(undefined4 *)(puVar40 + -8) =
           *(undefined4 *)((int)pvVar4 + ((pvVar18->W + 0x36) * 0xf + local_24) * 4);
      *(undefined1 **)(puVar40 + -0xc) = &stack0xffffff88 + iVar14;
      *(undefined4 **)(puVar40 + -0x10) = puVar20;
      *(void **)(puVar40 + -0x14) = pvVar19;
      *(int **)(puVar40 + -0x18) = piVar7;
      *(int *)(puVar40 + -0x1c) = iVar22;
      *(int *)(puVar40 + -0x20) = (int)pvVar4 + 0xb34;
      *(int *)(puVar40 + -0x24) = local_24;
      *(undefined4 *)(puVar40 + -0x28) = 0x5b0e5f;
      _vp_couple_quantize_normalize
                (*(int *)(puVar40 + -0x24),*(vorbis_info_psy_global **)(puVar40 + -0x20),
                 *(vorbis_look_psy **)(puVar40 + -0x1c),*(vorbis_info_mapping0 **)(puVar40 + -0x18),
                 *(float ***)(puVar40 + -0x14),*(int ***)(puVar40 + -0x10),*(int **)(puVar40 + -0xc)
                 ,*(int *)(puVar40 + -8),*(int *)(puVar40 + -4));
      param_1 = (vorbis_block *)0x0;
      if (0 < *piVar7) {
        local_38 = piVar7 + 0x111;
        puVar37 = puVar40;
        do {
          iVar29 = *local_38;
          local_4c = 0;
          local_1c = 0;
          if (0 < pvVar2->channels) {
            puVar32 = puVar20;
            local_64 = (undefined4 *)(&stack0xffffff88 + iVar24 * -8 + iVar15 + iVar14);
            local_50 = piVar7;
            do {
              local_50 = local_50 + 1;
              if ((vorbis_block *)*local_50 == param_1) {
                *local_64 = 0;
                if (*(int *)(&stack0xffffff88 + (iVar14 - (int)puVar20) + (int)puVar32) != 0) {
                  *local_64 = 1;
                }
                local_4c = local_4c + 1;
                *(undefined4 *)
                 (((int)(&stack0xffffff88 + iVar12 + iVar15 + iVar14) -
                  (int)(&stack0xffffff88 + iVar24 * -8 + iVar15 + iVar14)) + (int)local_64) =
                     *puVar32;
                local_64 = local_64 + 1;
              }
              local_1c = local_1c + 1;
              puVar32 = puVar32 + 1;
            } while (local_1c < pvVar2->channels);
          }
          pcVar13 = *(code **)(*(int *)(&_residue_P + *(int *)((int)pvVar4 + iVar29 * 4 + 0x520) * 4
                                       ) + 0x14);
          *(int *)(puVar37 + -4) = local_4c;
          *(undefined1 **)(puVar37 + -8) = &stack0xffffff88 + iVar24 * -8 + iVar15 + iVar14;
          uVar30 = *(undefined4 *)(*(int *)((int)pvVar3 + 0x34) + iVar29 * 4);
          *(undefined1 **)(puVar37 + -0xc) = &stack0xffffff88 + iVar12 + iVar15 + iVar14;
          *(undefined4 *)(puVar37 + -0x10) = uVar30;
          *(vorbis_block **)(puVar37 + -0x14) = pvVar18;
          puVar38 = (undefined4 *)(puVar37 + -0x18);
          *(undefined4 *)(puVar37 + -0x18) = 0x5b0f39;
          uVar30 = (*pcVar13)();
          iVar33 = 0;
          iVar31 = 0;
          local_50 = piVar7;
          if (0 < pvVar2->channels) {
            do {
              local_50 = local_50 + 1;
              if ((vorbis_block *)*local_50 == param_1) {
                *(undefined4 *)(&stack0xffffff88 + iVar31 * 4 + iVar12 + iVar15 + iVar14) =
                     puVar20[iVar33];
                iVar31 = iVar31 + 1;
              }
              iVar33 = iVar33 + 1;
            } while (iVar33 < pvVar2->channels);
          }
          pcVar13 = *(code **)(*(int *)(&_residue_P + *(int *)((int)pvVar4 + iVar29 * 4 + 0x520) * 4
                                       ) + 0x18);
          puVar38[4] = param_1;
          puVar38[3] = uVar30;
          puVar38[2] = iVar31;
          puVar38[1] = &stack0xffffff88 + iVar24 * -8 + iVar15 + iVar14;
          uVar30 = *(undefined4 *)(*(int *)((int)pvVar3 + 0x34) + iVar29 * 4);
          *puVar38 = &stack0xffffff88 + iVar12 + iVar15 + iVar14;
          puVar38[-1] = uVar30;
          puVar38[-2] = pvVar18;
          puVar38[-3] = uVar11;
          puVar39 = puVar38 + -4;
          puVar38[-4] = 0x5b0faa;
          (*pcVar13)();
          local_38 = local_38 + 1;
          param_1 = (vorbis_block *)((int)&param_1->pcm + 1);
          puVar40 = (undefined1 *)((int)puVar39 + 0x20);
          puVar37 = (undefined1 *)((int)puVar39 + 0x20);
        } while ((int)param_1 < *piVar7);
      }
      local_24 = local_24 + 1;
      local_34 = (float *)((int)local_34 + 4);
      local_30 = local_30 + 1;
      *(vorbis_block **)(puVar40 + -4) = pvVar18;
      *(undefined4 *)(puVar40 + -8) = 0x5b0fd7;
      iVar29 = vorbis_bitrate_managed(*(vorbis_block **)(puVar40 + -4));
    } while (local_24 <= (int)((-(uint)(iVar29 != 0) & 7) + 7));
  }
  return 0;
}
