/*
 * Entry: 005b5780
 * Name: vorbis_lpc_to_lsp
 * Namespace: Global
 * Signature: int vorbis_lpc_to_lsp(float * param_1, float * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl vorbis_lpc_to_lsp(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  uint uVar8;
  undefined1 *puVar9;
  undefined1 *puVar11;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  float10 fVar17;
  uint auStack_64 [3];
  size_t asStack_58 [2];
  uint auStack_50 [2];
  size_t asStack_48 [3];
  float afStack_3c [2];
  int iStack_34;
  float *local_1c;
  float *local_18;
  int local_8;
  undefined4 *puVar10;
  undefined4 *puVar12;
  
  uVar13 = param_3 + 1 >> 1;
  iVar16 = uVar13 * 4 + 4;
  iStack_34 = 0x5b57a2;
  iVar15 = -iVar16;
  puVar9 = &stack0xffffffd0 + iVar16 * -4;
  *(undefined4 *)((int)&iStack_34 + iVar15) = 0x5b57ac;
  *(undefined4 *)((int)&iStack_34 + iVar16 * -2) = 0x5b57b6;
  *(undefined4 *)((int)&iStack_34 + iVar16 * -3) = 0x5b57c0;
  *(undefined4 *)(&stack0xffffffd0 + uVar13 * 4 + iVar15) = 0x3f800000;
  uVar8 = param_3 >> 1;
  local_8 = 1;
  if (3 < (int)uVar13) {
    uVar14 = uVar13 >> 2;
    local_8 = uVar14 * 4 + 1;
    pfVar5 = param_1 + 2;
    pfVar4 = param_1 + param_3 + -3;
    pfVar7 = (float *)((int)afStack_3c + uVar13 * 4 + iVar15);
    do {
      uVar14 = uVar14 - 1;
      pfVar7[2] = pfVar4[2] + pfVar5[-2];
      pfVar7[1] = pfVar4[1] + pfVar5[-1];
      *pfVar7 = *pfVar4 + *pfVar5;
      pfVar7[-1] = pfVar4[-1] + pfVar5[1];
      pfVar5 = pfVar5 + 4;
      pfVar4 = pfVar4 + -4;
      pfVar7 = pfVar7 + -4;
    } while (uVar14 != 0);
  }
  if (local_8 <= (int)uVar13) {
    local_18 = param_1 + local_8 + -1;
    iVar6 = uVar13 - local_8;
    iVar3 = param_3 - local_8;
    local_8 = iVar6 + 1;
    pfVar5 = param_1 + iVar3;
    local_1c = (float *)(&stack0xffffffd0 + iVar6 * 4 + iVar15);
    do {
      fVar1 = *pfVar5;
      fVar2 = *local_18;
      local_18 = local_18 + 1;
      pfVar5 = pfVar5 + -1;
      *local_1c = fVar1 + fVar2;
      local_8 = local_8 + -1;
      local_1c = local_1c + -1;
    } while (local_8 != 0);
  }
  *(undefined4 *)(&stack0xffffffd0 + uVar8 * 4 + iVar16 * -2) = 0x3f800000;
  local_8 = 1;
  if (3 < (int)uVar8) {
    uVar14 = uVar8 >> 2;
    local_8 = uVar14 * 4 + 1;
    pfVar5 = param_1 + 2;
    pfVar4 = param_1 + param_3 + -3;
    pfVar7 = (float *)((int)afStack_3c + uVar8 * 4 + iVar16 * -2);
    do {
      uVar14 = uVar14 - 1;
      pfVar7[2] = pfVar5[-2] - pfVar4[2];
      pfVar7[1] = pfVar5[-1] - pfVar4[1];
      *pfVar7 = *pfVar5 - *pfVar4;
      pfVar7[-1] = pfVar5[1] - pfVar4[-1];
      pfVar5 = pfVar5 + 4;
      pfVar4 = pfVar4 + -4;
      pfVar7 = pfVar7 + -4;
    } while (uVar14 != 0);
  }
  if (local_8 <= (int)uVar8) {
    pfVar4 = param_1 + local_8 + -1;
    pfVar5 = param_1 + (param_3 - local_8);
    iVar3 = (uVar8 - local_8) + 1;
    pfVar7 = (float *)(&stack0xffffffd0 + (uVar8 - local_8) * 4 + iVar16 * -2);
    do {
      fVar1 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      fVar2 = *pfVar5;
      pfVar5 = pfVar5 + -1;
      iVar3 = iVar3 + -1;
      *pfVar7 = fVar1 - fVar2;
      pfVar7 = pfVar7 + -1;
    } while (iVar3 != 0);
  }
  if ((int)uVar8 < (int)uVar13) {
    iVar3 = 2;
    if (1 < (int)uVar8) {
      if (3 < (int)(uVar8 - 1)) {
        uVar14 = uVar8 - 1 >> 2;
        iVar3 = uVar14 * 4 + 2;
        pfVar5 = (float *)((int)afStack_3c + uVar8 * 4 + iVar16 * -2);
        do {
          uVar14 = uVar14 - 1;
          fVar1 = pfVar5[1];
          pfVar5[1] = pfVar5[3] + fVar1;
          fVar2 = *pfVar5;
          *pfVar5 = fVar2 + pfVar5[2];
          pfVar5[-1] = pfVar5[-1] + pfVar5[3] + fVar1;
          pfVar5[-2] = fVar2 + pfVar5[2] + pfVar5[-2];
          pfVar5 = pfVar5 + -4;
        } while (uVar14 != 0);
      }
      if (iVar3 <= (int)uVar8) {
        iVar6 = (uVar8 - iVar3) + 1;
        pfVar5 = (float *)(&stack0xffffffd0 + (uVar8 - iVar3) * 4 + iVar16 * -2);
        do {
          iVar6 = iVar6 + -1;
          *pfVar5 = pfVar5[2] + *pfVar5;
          pfVar5 = pfVar5 + -1;
        } while (iVar6 != 0);
      }
    }
  }
  else {
    iVar3 = 1;
    if (3 < (int)uVar13) {
      uVar14 = uVar13 >> 2;
      iVar3 = uVar14 * 4 + 1;
      pfVar5 = (float *)((int)afStack_3c + uVar13 * 4 + iVar15 + 4);
      do {
        fVar1 = pfVar5[1];
        uVar14 = uVar14 - 1;
        pfVar5[1] = fVar1 - pfVar5[2];
        fVar1 = *pfVar5 - (fVar1 - pfVar5[2]);
        *pfVar5 = fVar1;
        fVar1 = pfVar5[-1] - fVar1;
        pfVar5[-1] = fVar1;
        pfVar5[-2] = pfVar5[-2] - fVar1;
        pfVar5 = pfVar5 + -4;
      } while (uVar14 != 0);
    }
    if (iVar3 <= (int)uVar13) {
      iVar6 = (uVar13 - iVar3) + 1;
      pfVar5 = (float *)(&stack0xffffffd0 + (uVar13 - iVar3) * 4 + iVar15);
      do {
        iVar6 = iVar6 + -1;
        *pfVar5 = *pfVar5 - pfVar5[1];
        pfVar5 = pfVar5 + -1;
      } while (iVar6 != 0);
    }
    iVar3 = 1;
    if (3 < (int)uVar8) {
      uVar14 = uVar8 >> 2;
      iVar3 = uVar14 * 4 + 1;
      pfVar5 = (float *)((int)afStack_3c + uVar8 * 4 + iVar16 * -2 + 4);
      do {
        uVar14 = uVar14 - 1;
        fVar1 = pfVar5[1];
        pfVar5[1] = pfVar5[2] + fVar1;
        fVar1 = pfVar5[2] + fVar1 + *pfVar5;
        *pfVar5 = fVar1;
        fVar1 = fVar1 + pfVar5[-1];
        pfVar5[-1] = fVar1;
        pfVar5[-2] = fVar1 + pfVar5[-2];
        pfVar5 = pfVar5 + -4;
      } while (uVar14 != 0);
    }
    if (iVar3 <= (int)uVar8) {
      iVar6 = (uVar8 - iVar3) + 1;
      pfVar5 = (float *)(&stack0xffffffd0 + (uVar8 - iVar3) * 4 + iVar16 * -2);
      do {
        iVar6 = iVar6 + -1;
        *pfVar5 = pfVar5[1] + *pfVar5;
        pfVar5 = pfVar5 + -1;
      } while (iVar6 != 0);
    }
  }
  (&iStack_34)[-iVar16] = 0x5b5aab;
  cheby(*(float **)(&stack0xffffffd0 + iVar16 * -4),*(int *)(&stack0xffffffd4 + iVar16 * -4));
  (&iStack_34)[-iVar16] = 0x5b5ab5;
  cheby(*(float **)(&stack0xffffffd0 + iVar16 * -4),*(int *)(&stack0xffffffd4 + iVar16 * -4));
  (&iStack_34)[-iVar16] = (int)(&stack0xffffffd0 + iVar16 * -3);
  afStack_3c[1 - iVar16] = (float)(&stack0xffffffd0 + iVar15);
  afStack_3c[-iVar16] = 8.389595e-39;
  iVar3 = Laguerre_With_Deflation
                    ((float *)afStack_3c[1 - iVar16],(&iStack_34)[-iVar16],
                     *(float **)(&stack0xffffffd0 + iVar16 * -4));
  if (iVar3 == 0) {
    (&iStack_34)[-iVar16] = (int)(&stack0xffffffd0 + iVar16 * -4);
    afStack_3c[1 - iVar16] = (float)(&stack0xffffffd0 + iVar16 * -2);
    afStack_3c[-iVar16] = 8.389631e-39;
    iVar3 = Laguerre_With_Deflation
                      ((float *)afStack_3c[1 - iVar16],(&iStack_34)[-iVar16],
                       *(float **)(&stack0xffffffd0 + iVar16 * -4));
    if (iVar3 == 0) {
      (&iStack_34)[-iVar16] = (int)(&stack0xffffffd0 + iVar16 * -3);
      afStack_3c[1 - iVar16] = (float)(&stack0xffffffd0 + iVar15);
      afStack_3c[-iVar16] = 8.389664e-39;
      Newton_Raphson((float *)afStack_3c[1 - iVar16],(&iStack_34)[-iVar16],
                     *(float **)(&stack0xffffffd0 + iVar16 * -4));
      afStack_3c[-iVar16] = (float)(&stack0xffffffd0 + iVar16 * -4);
      asStack_48[2 - iVar16] = (size_t)(&stack0xffffffd0 + iVar16 * -2);
      asStack_48[1 - iVar16] = 0x5b5b07;
      Newton_Raphson((float *)asStack_48[2 - iVar16],(int)afStack_3c[-iVar16],
                     (float *)afStack_3c[1 - iVar16]);
      asStack_48[1 - iVar16] = (size_t)comp;
      asStack_48[-iVar16] = 4;
      auStack_50[1 - iVar16] = uVar13;
      auStack_50[-iVar16] = (uint)(&stack0xffffffd0 + iVar16 * -3);
      asStack_58[1 - iVar16] = 0x5b5b1b;
      qsort((void *)auStack_50[-iVar16],auStack_50[1 - iVar16],asStack_48[-iVar16],
            (_PtFuncCompare *)asStack_48[1 - iVar16]);
      asStack_58[1 - iVar16] = (size_t)comp;
      asStack_58[-iVar16] = 4;
      auStack_64[2 - iVar16] = uVar8;
      auStack_64[1 - iVar16] = (uint)(&stack0xffffffd0 + iVar16 * -4);
      auStack_64[-iVar16] = 0x5b5b29;
      qsort((void *)auStack_64[1 - iVar16],auStack_64[2 - iVar16],asStack_58[-iVar16],
            (_PtFuncCompare *)asStack_58[1 - iVar16]);
      iVar15 = 0;
      puVar11 = &stack0xffffffd0 + iVar16 * -4;
      if (0 < (int)uVar13) {
        do {
          puVar10 = (undefined4 *)(puVar9 + -4);
          puVar9 = puVar9 + -4;
          *puVar10 = 0x5b5b3d;
          fVar17 = (float10)__CIacos();
          param_2[iVar15 * 2] = (float)fVar17;
          iVar15 = iVar15 + 1;
          puVar11 = puVar9;
        } while (iVar15 < (int)uVar13);
      }
      iVar16 = 0;
      if (0 < (int)uVar8) {
        pfVar5 = param_2 + 1;
        do {
          puVar12 = (undefined4 *)(puVar11 + -4);
          puVar11 = puVar11 + -4;
          *puVar12 = 0x5b5b5f;
          fVar17 = (float10)__CIacos();
          *pfVar5 = (float)fVar17;
          iVar16 = iVar16 + 1;
          pfVar5 = pfVar5 + 2;
        } while (iVar16 < (int)uVar8);
      }
      return 0;
    }
  }
  return -1;
}
