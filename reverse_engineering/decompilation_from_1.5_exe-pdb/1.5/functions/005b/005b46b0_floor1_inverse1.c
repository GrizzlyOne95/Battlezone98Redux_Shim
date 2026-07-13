/*
 * Entry: 005b46b0
 * Name: floor1_inverse1
 * Namespace: Global
 * Signature: void * floor1_inverse1(vorbis_block * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor1_inverse1(vorbis_block *param_1,void *param_2)

{
  oggpack_buffer *poVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  long lVar10;
  int iVar11;
  byte bVar12;
  int *piVar13;
  long *plVar14;
  uint uVar15;
  int local_28;
  int local_24;
  int *local_20;
  int local_c;
  
  piVar2 = *(int **)((int)param_2 + 0x510);
  iVar11 = *(int *)((int)param_1->vd->vi->codec_setup + 0xb20);
  poVar1 = &param_1->opb;
  iVar5 = oggpack_read(poVar1,1);
  if (iVar5 != 1) {
    return (void *)0x0;
  }
  puVar6 = _vorbis_block_alloc(param_1,*(int *)((int)param_2 + 0x504) * 4);
  iVar5 = 0;
  for (uVar7 = *(int *)((int)param_2 + 0x50c) - 1; uVar7 != 0; uVar7 = uVar7 >> 1) {
    iVar5 = iVar5 + 1;
  }
  uVar8 = oggpack_read(poVar1,iVar5);
  *puVar6 = uVar8;
  iVar5 = 0;
  for (uVar7 = *(int *)((int)param_2 + 0x50c) - 1; uVar7 != 0; uVar7 = uVar7 >> 1) {
    iVar5 = iVar5 + 1;
  }
  uVar8 = oggpack_read(poVar1,iVar5);
  puVar6[1] = uVar8;
  local_28 = 0;
  local_24 = 2;
  local_20 = piVar2;
  if (0 < *piVar2) {
    do {
      local_20 = local_20 + 1;
      iVar5 = *local_20;
      iVar3 = piVar2[iVar5 + 0x20];
      bVar12 = (byte)piVar2[iVar5 + 0x30];
      uVar7 = 0;
      if ((piVar2[iVar5 + 0x30] != 0) &&
         (uVar7 = vorbis_book_decode((codebook *)(iVar11 + piVar2[iVar5 + 0x40] * 0x38),poVar1),
         uVar7 == 0xffffffff)) {
        return (void *)0x0;
      }
      local_c = 0;
      if (0 < iVar3) {
        plVar14 = puVar6 + local_24;
        do {
          uVar9 = (1 << (bVar12 & 0x1f)) - 1U & uVar7;
          uVar7 = (int)uVar7 >> (bVar12 & 0x1f);
          if (piVar2[uVar9 + iVar5 * 8 + 0x50] < 0) {
            *plVar14 = 0;
          }
          else {
            lVar10 = vorbis_book_decode((codebook *)
                                        (iVar11 + piVar2[uVar9 + iVar5 * 8 + 0x50] * 0x38),poVar1);
            *plVar14 = lVar10;
            if (lVar10 == -1) {
              return (void *)0x0;
            }
          }
          local_c = local_c + 1;
          plVar14 = plVar14 + 1;
        } while (local_c < iVar3);
      }
      local_24 = local_24 + iVar3;
      local_28 = local_28 + 1;
    } while (local_28 < *piVar2);
  }
  local_28 = 2;
  if (2 < *(int *)((int)param_2 + 0x504)) {
    local_20 = piVar2 + 0xd3;
    piVar13 = (int *)((int)param_2 + 0x30c);
    do {
      uVar7 = (puVar6[*piVar13] & 0x7fff) - (puVar6[piVar13[0x3f]] & 0x7fff);
      iVar11 = (int)(((uVar7 ^ (int)uVar7 >> 0x1f) - ((int)uVar7 >> 0x1f)) *
                    (*local_20 - piVar2[piVar13[0x3f] + 0xd1])) /
               (piVar2[*piVar13 + 0xd1] - piVar2[piVar13[0x3f] + 0xd1]);
      if ((int)uVar7 < 0) {
        iVar11 = -iVar11;
      }
      uVar15 = (puVar6[piVar13[0x3f]] & 0x7fff) + iVar11;
      uVar9 = *(int *)((int)param_2 + 0x50c) - uVar15;
      uVar7 = uVar9;
      if ((int)uVar15 <= (int)uVar9) {
        uVar7 = uVar15;
      }
      uVar4 = puVar6[local_28];
      if (uVar4 == 0) {
        puVar6[local_28] = uVar15 | 0x8000;
      }
      else {
        if ((int)uVar4 < (int)(uVar7 * 2)) {
          if ((uVar4 & 1) == 0) {
            iVar11 = (int)uVar4 >> 1;
          }
          else {
            iVar11 = -((int)(uVar4 + 1) >> 1);
          }
        }
        else if ((int)uVar15 < (int)uVar9) {
          iVar11 = uVar4 - uVar15;
        }
        else {
          iVar11 = (uVar9 - uVar4) + -1;
        }
        puVar6[local_28] = iVar11 + uVar15 & 0x7fff;
        puVar6[piVar13[0x3f]] = puVar6[piVar13[0x3f]] & 0x7fff;
        puVar6[*piVar13] = puVar6[*piVar13] & 0x7fff;
      }
      local_20 = local_20 + 1;
      local_28 = local_28 + 1;
      piVar13 = piVar13 + 1;
    } while (local_28 < *(int *)((int)param_2 + 0x504));
  }
  return puVar6;
}
