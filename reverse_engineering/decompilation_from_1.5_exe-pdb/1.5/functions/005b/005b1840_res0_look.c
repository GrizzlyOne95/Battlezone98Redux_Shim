/*
 * Entry: 005b1840
 * Name: res0_look
 * Namespace: Global
 * Signature: void * res0_look(vorbis_dsp_state * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl res0_look(vorbis_dsp_state *param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  void *pvVar4;
  uint uVar5;
  void *pvVar6;
  int iVar7;
  void *pvVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  uint *puVar14;
  size_t sVar15;
  int iVar16;
  int local_20;
  int local_1c;
  size_t local_14;
  uint local_10;
  
  puVar3 = calloc(1,0x2c);
  iVar10 = *(int *)((int)param_2 + 0x14);
  pvVar8 = param_1->vi->codec_setup;
  iVar7 = *(int *)((int)pvVar8 + 0xb20);
  iVar1 = *(int *)(iVar7 + iVar10 * 0x38);
  puVar3[3] = iVar7;
  local_20 = 0;
  local_14 = 0;
  sVar15 = *(size_t *)((int)param_2 + 0xc);
  *puVar3 = param_2;
  puVar3[1] = sVar15;
  puVar3[4] = iVar7 + iVar10 * 0x38;
  pvVar4 = calloc(sVar15,4);
  puVar3[5] = pvVar4;
  local_1c = 0;
  if (0 < (int)puVar3[1]) {
    puVar14 = (uint *)((int)param_2 + 0x18);
    do {
      uVar5 = *puVar14;
      sVar15 = 0;
      if (uVar5 != 0) {
        do {
          sVar15 = sVar15 + 1;
          uVar5 = uVar5 >> 1;
        } while (uVar5 != 0);
        if (sVar15 != 0) {
          if ((int)local_14 < (int)sVar15) {
            local_14 = sVar15;
          }
          pvVar6 = calloc(sVar15,4);
          *(void **)((int)pvVar4 + local_1c * 4) = pvVar6;
          iVar10 = 0;
          local_10 = 1;
          if (0 < (int)sVar15) {
            piVar12 = (int *)((int)param_2 + local_20 * 4 + 0x118);
            do {
              if ((*puVar14 & local_10) != 0) {
                local_20 = local_20 + 1;
                *(int *)(*(int *)((int)pvVar4 + local_1c * 4) + iVar10 * 4) =
                     *(int *)((int)pvVar8 + 0xb20) + *piVar12 * 0x38;
                piVar12 = piVar12 + 1;
              }
              iVar10 = iVar10 + 1;
              local_10 = local_10 << 1 | (uint)((int)local_10 < 0);
            } while (iVar10 < (int)sVar15);
          }
        }
      }
      local_1c = local_1c + 1;
      puVar14 = puVar14 + 1;
    } while (local_1c < (int)puVar3[1]);
  }
  puVar3[6] = 1;
  if (0 < iVar1) {
    iVar7 = 1;
    iVar10 = iVar1;
    do {
      iVar7 = iVar7 * puVar3[1];
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    puVar3[6] = iVar7;
  }
  iVar10 = puVar3[6];
  puVar3[2] = local_14;
  pvVar8 = malloc(iVar10 * 4);
  iVar7 = 0;
  puVar3[7] = pvVar8;
  if (0 < iVar10) {
    iVar2 = puVar3[1];
    do {
      pvVar4 = malloc(iVar1 * 4);
      iVar11 = 0;
      *(void **)((int)pvVar8 + iVar7 * 4) = pvVar4;
      iVar13 = iVar7;
      iVar16 = iVar10;
      if (0 < iVar1) {
        do {
          iVar16 = iVar16 / iVar2;
          iVar9 = iVar13 / iVar16;
          iVar11 = iVar11 + 1;
          iVar13 = iVar13 - iVar9 * iVar16;
          *(int *)(*(int *)((int)pvVar8 + iVar7 * 4) + -4 + iVar11 * 4) = iVar9;
        } while (iVar11 < iVar1);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < iVar10);
  }
  return puVar3;
}
