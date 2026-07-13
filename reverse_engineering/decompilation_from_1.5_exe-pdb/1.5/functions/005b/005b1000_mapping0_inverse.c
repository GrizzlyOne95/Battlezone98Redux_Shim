/*
 * Entry: 005b1000
 * Name: mapping0_inverse
 * Namespace: Global
 * Signature: int mapping0_inverse(vorbis_block * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl mapping0_inverse(vorbis_block *param_1,void *param_2)

{
  float fVar1;
  float fVar2;
  vorbis_info *pvVar3;
  void *pvVar4;
  void *pvVar5;
  int iVar6;
  code *pcVar7;
  float **ppfVar8;
  float *pfVar9;
  float *pfVar10;
  uint uVar11;
  int *piVar12;
  uint *puVar13;
  uint *puVar14;
  float *pfVar15;
  int iVar16;
  float *pfVar17;
  undefined1 *puVar18;
  undefined1 *puVar19;
  undefined1 *puVar20;
  undefined1 *puVar21;
  undefined1 *puVar22;
  undefined1 *puVar23;
  undefined1 *puVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined4 uStack_40;
  int *local_1c;
  int *local_14;
  int local_10;
  
  pvVar3 = param_1->vd->vi;
  pvVar4 = param_1->vd->backend_state;
  pvVar5 = pvVar3->codec_setup;
  iVar16 = *(int *)((int)pvVar5 + param_1->W * 4);
  param_1->pcmend = iVar16;
  iVar6 = pvVar3->channels;
  uStack_40 = 0x5b103e;
  puVar13 = (uint *)(&stack0xffffffc4 + iVar6 * -0xc);
  puVar20 = &stack0xffffffc4 + iVar6 * -0x10;
  puVar18 = &stack0xffffffc4 + iVar6 * -0x10;
  (&uStack_40)[-iVar6] = 0x5b1048;
  (&uStack_40)[iVar6 * -2] = 0x5b1052;
  (&uStack_40)[iVar6 * -3] = 0x5b105c;
  iVar25 = 0;
  if (0 < iVar6) {
    local_14 = param_2;
    do {
      local_14 = local_14 + 1;
      iVar26 = *(int *)((int)param_2 + *local_14 * 4 + 0x404);
      pcVar7 = *(code **)(*(int *)(&_floor_P + *(int *)((int)pvVar5 + iVar26 * 4 + 800) * 4) + 0x14)
      ;
      *(undefined4 *)(puVar18 + -4) = *(undefined4 *)(*(int *)((int)pvVar4 + 0x30) + iVar26 * 4);
      *(vorbis_block **)(puVar18 + -8) = param_1;
      puVar19 = puVar18 + -0xc;
      *(undefined4 *)(puVar18 + -0xc) = 0x5b10b8;
      uVar11 = (*pcVar7)();
      puVar13[-iVar6] = uVar11;
      ppfVar8 = param_1->pcm;
      *(uint *)(puVar19 + -4) = (uint)(iVar16 * 4) >> 1;
      *(undefined4 *)(puVar19 + -8) = 0;
      *puVar13 = (uint)(uVar11 != 0);
      *(float **)(puVar19 + -0xc) = ppfVar8[iVar25];
      *(undefined4 *)(puVar19 + -0x10) = 0x5b10d8;
      memset();
      iVar25 = iVar25 + 1;
      puVar20 = puVar19 + 8;
      puVar18 = puVar19 + 8;
      puVar13 = puVar13 + 1;
    } while (iVar25 < pvVar3->channels);
  }
  iVar25 = *(int *)((int)param_2 + 0x484);
  if (0 < iVar25) {
    piVar12 = (int *)((int)param_2 + 0x888);
    do {
      if ((*(int *)(&stack0xffffffc4 + piVar12[-0x100] * 4 + iVar6 * -0xc) != 0) ||
         (*(int *)(&stack0xffffffc4 + *piVar12 * 4 + iVar6 * -0xc) != 0)) {
        *(undefined4 *)(&stack0xffffffc4 + piVar12[-0x100] * 4 + iVar6 * -0xc) = 1;
        *(undefined4 *)(&stack0xffffffc4 + *piVar12 * 4 + iVar6 * -0xc) = 1;
      }
      piVar12 = piVar12 + 1;
      iVar25 = iVar25 + -1;
    } while (iVar25 != 0);
  }
  local_10 = 0;
  puVar24 = puVar20;
  if (0 < *(int *)param_2) {
    local_1c = (int *)((int)param_2 + 0x444);
    do {
      iVar25 = 0;
      iVar26 = 0;
      puVar13 = (uint *)(&stack0xffffffc4 + iVar6 * -8);
      local_14 = param_2;
      if (0 < pvVar3->channels) {
        do {
          local_14 = local_14 + 1;
          puVar14 = puVar13;
          if (*local_14 == local_10) {
            iVar26 = iVar26 + 1;
            puVar14 = puVar13 + 1;
            *puVar13 = (uint)(*(int *)(&stack0xffffffc4 + iVar25 * 4 + iVar6 * -0xc) != 0);
            puVar14[iVar6 + -1] = (uint)param_1->pcm[iVar25];
          }
          iVar25 = iVar25 + 1;
          puVar13 = puVar14;
        } while (iVar25 < pvVar3->channels);
      }
      iVar25 = *local_1c;
      pcVar7 = *(code **)(*(int *)(&_residue_P + *(int *)((int)pvVar5 + iVar25 * 4 + 0x520) * 4) +
                         0x1c);
      *(int *)(puVar20 + -4) = iVar26;
      *(undefined1 **)(puVar20 + -8) = &stack0xffffffc4 + iVar6 * -8;
      *(undefined1 **)(puVar20 + -0xc) = &stack0xffffffc4 + iVar6 * -4;
      *(undefined4 *)(puVar20 + -0x10) = *(undefined4 *)(*(int *)((int)pvVar4 + 0x34) + iVar25 * 4);
      *(vorbis_block **)(puVar20 + -0x14) = param_1;
      puVar21 = puVar20 + -0x18;
      *(undefined4 *)(puVar20 + -0x18) = 0x5b11d4;
      (*pcVar7)();
      local_1c = local_1c + 1;
      local_10 = local_10 + 1;
      puVar20 = puVar21 + 0x14;
      puVar24 = puVar21 + 0x14;
    } while (local_10 < *(int *)param_2);
  }
  iVar25 = *(int *)((int)param_2 + 0x484) + -1;
  if (-1 < iVar25) {
    iVar16 = iVar16 / 2;
    piVar12 = (int *)((int)param_2 + iVar25 * 4 + 0x888);
    do {
      pfVar9 = param_1->pcm[piVar12[-0x100]];
      pfVar10 = param_1->pcm[*piVar12];
      iVar26 = 0;
      if (3 < iVar16) {
        pfVar15 = pfVar9 + 1;
        iVar28 = (int)pfVar10 - (int)pfVar9;
        iVar27 = (iVar16 - 4U >> 2) + 1;
        pfVar17 = pfVar10 + 3;
        iVar26 = iVar27 * 4;
        do {
          fVar1 = pfVar15[-1];
          fVar2 = pfVar17[-3];
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              pfVar17[-3] = fVar1;
              fVar1 = fVar1 - fVar2;
              goto LAB_005b12a2;
            }
            pfVar17[-3] = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            pfVar17[-3] = fVar1;
            fVar1 = fVar1 + fVar2;
LAB_005b12a2:
            pfVar15[-1] = fVar1;
          }
          else {
            pfVar17[-3] = fVar1 - fVar2;
          }
          fVar1 = *pfVar15;
          fVar2 = *(float *)(iVar28 + (int)pfVar15);
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              *(float *)(iVar28 + (int)pfVar15) = fVar1;
              fVar1 = fVar1 - fVar2;
              goto LAB_005b12eb;
            }
            *(float *)(iVar28 + (int)pfVar15) = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            *(float *)(iVar28 + (int)pfVar15) = fVar1;
            fVar1 = fVar1 + fVar2;
LAB_005b12eb:
            *pfVar15 = fVar1;
          }
          else {
            *(float *)(iVar28 + (int)pfVar15) = fVar1 - fVar2;
          }
          fVar1 = pfVar15[1];
          fVar2 = pfVar17[-1];
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              pfVar17[-1] = fVar1;
              fVar1 = fVar1 - fVar2;
              goto LAB_005b1334;
            }
            pfVar17[-1] = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            pfVar17[-1] = fVar1;
            fVar1 = fVar1 + fVar2;
LAB_005b1334:
            pfVar15[1] = fVar1;
          }
          else {
            pfVar17[-1] = fVar1 - fVar2;
          }
          fVar1 = pfVar15[2];
          fVar2 = *pfVar17;
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              *pfVar17 = fVar1;
              fVar1 = fVar1 - fVar2;
              goto LAB_005b1379;
            }
            *pfVar17 = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            *pfVar17 = fVar1;
            fVar1 = fVar1 + fVar2;
LAB_005b1379:
            pfVar15[2] = fVar1;
          }
          else {
            *pfVar17 = fVar1 - fVar2;
          }
          pfVar15 = pfVar15 + 4;
          pfVar17 = pfVar17 + 4;
          iVar27 = iVar27 + -1;
        } while (iVar27 != 0);
      }
      if (iVar26 < iVar16) {
        pfVar15 = pfVar9 + iVar26;
        iVar27 = (int)pfVar10 - (int)pfVar9;
        iVar26 = iVar16 - iVar26;
        do {
          fVar1 = *pfVar15;
          fVar2 = *(float *)((int)pfVar15 + iVar27);
          if (fVar1 <= 0.0) {
            if (fVar2 <= 0.0) {
              *(float *)((int)pfVar15 + iVar27) = fVar1;
              fVar1 = fVar1 - fVar2;
              goto LAB_005b13f0;
            }
            *(float *)((int)pfVar15 + iVar27) = fVar2 + fVar1;
          }
          else if (fVar2 <= 0.0) {
            *(float *)((int)pfVar15 + iVar27) = fVar1;
            fVar1 = fVar1 + fVar2;
LAB_005b13f0:
            *pfVar15 = fVar1;
          }
          else {
            *(float *)((int)pfVar15 + iVar27) = fVar1 - fVar2;
          }
          pfVar15 = pfVar15 + 1;
          iVar26 = iVar26 + -1;
        } while (iVar26 != 0);
      }
      piVar12 = piVar12 + -1;
      iVar25 = iVar25 + -1;
    } while (-1 < iVar25);
  }
  iVar16 = 0;
  puVar22 = puVar24;
  piVar12 = param_2;
  if (0 < pvVar3->channels) {
    do {
      iVar25 = *(int *)((int)param_2 + piVar12[1] * 4 + 0x404);
      pcVar7 = *(code **)(*(int *)(&_floor_P + *(int *)((int)pvVar5 + iVar25 * 4 + 800) * 4) + 0x18)
      ;
      *(float **)(puVar22 + -4) = param_1->pcm[iVar16];
      *(undefined4 *)(puVar22 + -8) = *(undefined4 *)(&stack0xffffffc4 + iVar16 * 4 + iVar6 * -0x10)
      ;
      *(undefined4 *)(puVar22 + -0xc) = *(undefined4 *)(*(int *)((int)pvVar4 + 0x30) + iVar25 * 4);
      *(vorbis_block **)(puVar22 + -0x10) = param_1;
      puVar23 = puVar22 + -0x14;
      *(undefined4 *)(puVar22 + -0x14) = 0x5b145c;
      (*pcVar7)();
      iVar16 = iVar16 + 1;
      puVar24 = puVar23 + 0x10;
      puVar22 = puVar23 + 0x10;
      piVar12 = piVar12 + 1;
    } while (iVar16 < pvVar3->channels);
  }
  iVar16 = 0;
  if (0 < pvVar3->channels) {
    do {
      pfVar9 = param_1->pcm[iVar16];
      iVar6 = param_1->W;
      *(float **)(puVar24 + -4) = pfVar9;
      *(float **)(puVar24 + -8) = pfVar9;
      *(undefined4 *)(puVar24 + -0xc) = **(undefined4 **)((int)pvVar4 + iVar6 * 4 + 0xc);
      *(undefined4 *)(puVar24 + -0x10) = 0x5b148e;
      mdct_backward(*(mdct_lookup **)(puVar24 + -0xc),*(float **)(puVar24 + -8),
                    *(float **)(puVar24 + -4));
      iVar16 = iVar16 + 1;
    } while (iVar16 < pvVar3->channels);
  }
  return 0;
}
