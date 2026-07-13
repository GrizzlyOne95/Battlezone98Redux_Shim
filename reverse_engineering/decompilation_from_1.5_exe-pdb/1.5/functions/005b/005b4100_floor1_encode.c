/*
 * Entry: 005b4100
 * Name: floor1_encode
 * Namespace: Global
 * Signature: int floor1_encode(oggpack_buffer * param_1, vorbis_block * param_2, vorbis_look_floor1 * param_3, int * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
floor1_encode(oggpack_buffer *param_1,vorbis_block *param_2,vorbis_look_floor1 *param_3,int *param_4
             ,int *param_5)

{
  int *piVar1;
  vorbis_info_floor1 *pvVar2;
  void *pvVar3;
  int iVar4;
  vorbis_info_floor1 *pvVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte bVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  int (*paiVar16) [8];
  int *unaff_ESI;
  uint uVar17;
  int unaff_EDI;
  int iVar18;
  int iVar19;
  int *local_164;
  int *local_160;
  int local_158;
  uint *local_154;
  int local_144 [16];
  int local_104 [65];
  
  pvVar2 = param_3->vi;
  local_158 = param_3->posts;
  pvVar3 = param_2->vd->vi->codec_setup;
  iVar4 = *(int *)((int)pvVar3 + 0xb20);
  if (param_4 == (int *)0x0) {
    oggpack_write(param_1,0,1);
    memset(param_5,0,(param_2->pcmend / 2) * 4);
    return 0;
  }
  iVar18 = 0;
  if (0 < local_158) {
    do {
      uVar12 = param_4[iVar18] & 0x7fff;
      switch(pvVar2->mult) {
      case 1:
        uVar12 = (int)uVar12 >> 2;
        break;
      case 2:
        uVar12 = (int)uVar12 >> 3;
        break;
      case 3:
        uVar12 = uVar12 / 0xc;
        break;
      case 4:
        uVar12 = (int)uVar12 >> 4;
      }
      param_4[iVar18] = param_4[iVar18] & 0x8000U | uVar12;
      iVar18 = iVar18 + 1;
    } while (iVar18 < local_158);
  }
  iVar18 = *param_4;
  iVar19 = param_4[1];
  if (2 < local_158) {
    local_164 = pvVar2->postlist + 2;
    local_154 = (uint *)(param_4 + 2);
    piVar6 = param_3->hineighbor;
    local_158 = local_158 + -2;
    do {
      iVar10 = piVar6[0x3f];
      iVar14 = *piVar6;
      uVar17 = param_4[iVar10] & 0x7fff;
      uVar12 = (param_4[iVar14] & 0x7fffU) - uVar17;
      iVar7 = (int)(((uVar12 ^ (int)uVar12 >> 0x1f) - ((int)uVar12 >> 0x1f)) *
                   (*local_164 - pvVar2->postlist[iVar10])) /
              (pvVar2->postlist[iVar14] - pvVar2->postlist[iVar10]);
      if ((int)uVar12 < 0) {
        iVar7 = -iVar7;
      }
      uVar13 = uVar17 + iVar7;
      uVar12 = *local_154;
      if (((uVar12 & 0x8000) == 0) && (uVar13 != uVar12)) {
        uVar15 = param_3->quant_q - uVar13;
        if ((int)uVar13 <= (int)uVar15) {
          uVar15 = uVar13;
        }
        iVar7 = uVar12 - uVar13;
        if (iVar7 < 0) {
          if (iVar7 < (int)-uVar15) {
            iVar7 = (uVar15 - iVar7) + -1;
          }
          else {
            iVar7 = iVar7 * -2 + -1;
          }
        }
        else if (iVar7 < (int)uVar15) {
          iVar7 = iVar7 * 2;
        }
        else {
          iVar7 = iVar7 + uVar15;
        }
        *(int *)(((int)local_104 - (int)param_4) + (int)local_154) = iVar7;
        param_4[iVar10] = uVar17;
        param_4[iVar14] = param_4[iVar14] & 0x7fff;
      }
      else {
        *local_154 = uVar13 | 0x8000;
        *(undefined4 *)(((int)local_104 - (int)param_4) + (int)local_154) = 0;
      }
      piVar6 = piVar6 + 1;
      local_164 = local_164 + 1;
      local_154 = local_154 + 1;
      local_158 = local_158 + -1;
    } while (local_158 != 0);
  }
  local_104[0] = iVar18;
  local_104[1] = iVar19;
  oggpack_write(param_1,1,1);
  param_3->frames = param_3->frames + 1;
  uVar12 = param_3->quant_q - 1;
  iVar18 = 0;
  if (uVar12 != 0) {
    iVar18 = 0;
    uVar17 = uVar12;
    do {
      iVar18 = iVar18 + 1;
      uVar17 = uVar17 >> 1;
    } while (uVar17 != 0);
  }
  param_3->postbits = param_3->postbits + iVar18 * 2;
  iVar18 = 0;
  for (; uVar12 != 0; uVar12 = uVar12 >> 1) {
    iVar18 = iVar18 + 1;
  }
  oggpack_write(param_1,local_104[0],iVar18);
  iVar18 = 0;
  for (uVar12 = param_3->quant_q - 1; uVar12 != 0; uVar12 = uVar12 >> 1) {
    iVar18 = iVar18 + 1;
  }
  oggpack_write(param_1,local_104[1],iVar18);
  local_154 = (uint *)0x0;
  local_164 = (int *)0x2;
  pvVar5 = pvVar2;
  if (0 < pvVar2->partitions) {
    do {
      iVar18 = pvVar5->partitionclass[0];
      iVar19 = pvVar2->class_dim[iVar18];
      iVar10 = pvVar2->class_subs[iVar18];
      iVar7 = 1 << ((byte)iVar10 & 0x1f);
      iVar14 = 0;
      local_144[0] = 0;
      local_144[1] = 0;
      local_144[2] = 0;
      local_144[3] = 0;
      local_144[4] = 0;
      local_144[5] = 0;
      local_144[6] = 0;
      local_144[7] = 0;
      local_160 = (int *)0x0;
      if (iVar10 != 0) {
        iVar8 = 0;
        if (0 < iVar7) {
          paiVar16 = pvVar2->class_subbook + iVar18;
          do {
            if ((*paiVar16)[0] < 0) {
              local_144[iVar8 + 8] = 1;
            }
            else {
              local_144[iVar8 + 8] =
                   *(int *)(*(int *)((int)pvVar3 + (*paiVar16)[0] * 4 + 0x720) + 4);
            }
            iVar8 = iVar8 + 1;
            paiVar16 = (int (*) [8])(*paiVar16 + 1);
          } while (iVar8 < iVar7);
        }
        iVar8 = 0;
        if (0 < iVar19) {
          piVar6 = local_104 + (int)local_164;
          do {
            iVar9 = 0;
            if (0 < iVar7) {
              do {
                if (*piVar6 < local_144[iVar9 + 8]) {
                  local_144[iVar8] = iVar9;
                  break;
                }
                iVar9 = iVar9 + 1;
              } while (iVar9 < iVar7);
            }
            piVar1 = local_144 + iVar8;
            bVar11 = (byte)iVar14;
            iVar8 = iVar8 + 1;
            iVar14 = iVar14 + iVar10;
            piVar6 = piVar6 + 1;
            local_160 = (int *)((uint)local_160 | *piVar1 << (bVar11 & 0x1f));
          } while (iVar8 < iVar19);
        }
        iVar10 = vorbis_book_encode((codebook *)(iVar4 + pvVar2->class_book[iVar18] * 0x38),
                                    (int)local_160,param_1);
        param_3->phrasebits = param_3->phrasebits + iVar10;
      }
      iVar10 = 0;
      if (0 < iVar19) {
        piVar6 = local_104 + (int)local_164;
        do {
          iVar14 = pvVar2->class_subbook[iVar18][local_144[iVar10]];
          if (-1 < iVar14) {
            if (*piVar6 < *(int *)(iVar4 + 4 + iVar14 * 0x38)) {
              iVar14 = vorbis_book_encode((codebook *)(iVar4 + iVar14 * 0x38),*piVar6,param_1);
              param_3->postbits = param_3->postbits + iVar14;
            }
          }
          iVar10 = iVar10 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar10 < iVar19);
      }
      local_164 = (int *)((int)local_164 + iVar19);
      local_154 = (uint *)((int)local_154 + 1);
      pvVar5 = (vorbis_info_floor1 *)pvVar5->partitionclass;
    } while ((int)local_154 < pvVar2->partitions);
  }
  iVar18 = pvVar2->mult * *param_4;
  iVar4 = *(int *)((int)pvVar3 + param_2->W * 4);
  iVar19 = 0;
  local_164 = (int *)0x1;
  if (1 < param_3->posts) {
    local_160 = param_3->forward_index;
    iVar10 = iVar18;
    iVar14 = 0;
    do {
      local_160 = local_160 + 1;
      uVar12 = param_4[*local_160] & 0x7fff;
      iVar18 = iVar10;
      iVar7 = iVar14;
      if (uVar12 == param_4[*local_160]) {
        iVar7 = pvVar2->postlist[*local_160];
        iVar18 = pvVar2->mult * uVar12;
        render_line0(iVar4 / 2,iVar14,iVar10,(int)param_5,unaff_EDI,unaff_ESI);
        iVar19 = iVar7;
      }
      local_164 = (int *)((int)local_164 + 1);
      iVar10 = iVar18;
      iVar14 = iVar7;
    } while ((int)local_164 < param_3->posts);
  }
  if (iVar19 < param_2->pcmend / 2) {
    do {
      param_5[iVar19] = iVar18;
      iVar19 = iVar19 + 1;
    } while (iVar19 < param_2->pcmend / 2);
  }
  return 1;
}
