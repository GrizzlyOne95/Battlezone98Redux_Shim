/*
 * Entry: 005b3b30
 * Name: floor1_fit
 * Namespace: Global
 * Signature: int * floor1_fit(vorbis_block * param_1, vorbis_look_floor1 * param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

int * __cdecl
floor1_fit(vorbis_block *param_1,vorbis_look_floor1 *param_2,float *param_3,float *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  vorbis_info_floor1 *pvVar8;
  int *piVar9;
  int *piVar10;
  vorbis_info_floor1 *unaff_ESI;
  uint uVar11;
  float *unaff_EDI;
  lsfit_acc *plVar12;
  int *local_133c;
  int local_1338;
  vorbis_info_floor1 *local_1334;
  int *local_1330;
  int local_132c;
  int local_1328;
  int local_1324;
  int *local_1320;
  vorbis_info_floor1 local_131c;
  lsfit_acc local_e00 [63];
  undefined4 uStack_4;
  
  uStack_4 = 0x5b3b3a;
  pvVar8 = param_2->vi;
  iVar2 = param_2->posts;
  local_1328 = param_2->n;
  local_1338 = 0;
  local_133c = (int *)0x0;
  if (0 < iVar2) {
    piVar6 = local_131c.class_book + 3;
    for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar6 = -200;
      piVar6 = piVar6 + 1;
    }
  }
  if (0 < iVar2) {
    piVar6 = local_131c.partitionclass;
    for (iVar3 = iVar2; piVar6 = piVar6 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar6 = -200;
    }
    piVar6 = local_131c.class_subbook[6] + 4;
    for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar6 = 0;
      piVar6 = piVar6 + 1;
    }
    if (0 < iVar2) {
      piVar6 = local_131c.class_subbook[0xe] + 5;
      for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar6 = 1;
        piVar6 = piVar6 + 1;
      }
      piVar6 = local_131c.postlist + 0x35;
      for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar6 = -1;
        piVar6 = piVar6 + 1;
      }
    }
  }
  local_1334 = pvVar8;
  local_132c = iVar2;
  if (iVar2 == 0) {
    iVar1 = accumulate_fit(param_4,param_3,local_1328,local_1328,(lsfit_acc *)pvVar8,(int)unaff_EDI,
                           unaff_ESI);
  }
  else {
    iVar3 = 0;
    if (iVar2 == 1 || iVar2 + -1 < 0) {
      return (int *)0x0;
    }
    do {
      iVar1 = accumulate_fit(param_4,param_3,param_2->sorted_index[iVar3 + 1],local_1328,
                             (lsfit_acc *)pvVar8,(int)unaff_EDI,unaff_ESI);
      iVar1 = local_1338 + iVar1;
      iVar3 = iVar3 + 1;
      local_1338 = iVar1;
    } while (iVar3 < iVar2 + -1);
  }
  if (iVar1 != 0) {
    local_1330 = (int *)0xffffff38;
    local_133c = (int *)0xffffff38;
    fit_line(local_e00,(int)&local_1330,(int *)&local_133c,(int *)unaff_EDI,unaff_ESI);
    local_131c.class_book[3] = (int)local_1330;
    local_131c.partitionclass[1] = (int)local_1330;
    local_131c.partitionclass[2] = (int)local_133c;
    local_131c.class_book[4] = (int)local_133c;
    local_1338 = 2;
    if (2 < iVar2) {
      local_133c = param_2->reverse_index + 2;
      do {
        local_1328 = local_131c.class_subbook[6][*local_133c + 4];
        iVar3 = local_131c.postlist[*local_133c + -0xc];
        if (local_131c.postlist[local_1328 + 0x35] != iVar3) {
          iVar2 = param_2->reverse_index[local_1328];
          local_1324 = pvVar8->postlist[iVar3];
          piVar6 = (int *)local_131c.class_book[local_1328 + 3];
          local_131c.postlist[local_1328 + 0x35] = iVar3;
          if ((int)piVar6 < 0) {
            piVar6 = (int *)local_131c.partitionclass[local_1328 + 1];
          }
          else if (-1 < local_131c.partitionclass[local_1328 + 1]) {
            piVar6 = (int *)(local_131c.partitionclass[local_1328 + 1] + (int)piVar6 >> 1);
          }
          piVar9 = (int *)local_131c.class_book[iVar3 + 3];
          if ((int)piVar9 < 0) {
            piVar9 = (int *)local_131c.partitionclass[iVar3 + 1];
          }
          else if (-1 < local_131c.partitionclass[iVar3 + 1]) {
            piVar9 = (int *)((int)piVar9 + local_131c.partitionclass[iVar3 + 1] >> 1);
          }
          if ((piVar6 == (int *)0xffffffff) || (piVar9 == (int *)0xffffffff)) {
                    /* WARNING: Subroutine does not return */
            exit(1);
          }
          iVar1 = inspect_error(local_1324,(int)piVar6,(int)param_4,(int)param_3,(float *)local_1334
                                ,unaff_EDI,unaff_ESI);
          if (iVar1 != 0) {
            local_131c.partitions = -200;
            local_131c.partitionclass[0] = -200;
            local_1330 = (int *)0xffffff38;
            local_1320 = (int *)0xffffff38;
            pvVar8 = &local_131c;
            plVar12 = local_e00 + iVar2;
            local_1324 = fit_line(plVar12,(int)pvVar8,local_131c.partitionclass,(int *)unaff_EDI,
                                  unaff_ESI);
            iVar1 = *local_133c;
            iVar2 = fit_line(local_e00 + iVar1,(int)&local_1330,(int *)&local_1320,&plVar12->x0,
                             pvVar8);
            piVar5 = (int *)local_131c.partitionclass[0];
            piVar7 = (int *)local_131c.partitions;
            if (local_1324 != 0) {
              piVar5 = local_1330;
              piVar7 = piVar6;
            }
            piVar6 = local_1330;
            piVar10 = local_1320;
            if (iVar2 != 0) {
              piVar6 = piVar5;
              piVar10 = piVar9;
            }
            if ((local_1324 == 0) || (iVar2 == 0)) {
              local_131c.partitionclass[local_1328 + 1] = (int)piVar7;
              if (local_1328 == 0) {
                local_131c.class_book[3] = (int)piVar7;
              }
              local_131c.class_book[local_1338 + 3] = (int)piVar5;
              local_131c.partitionclass[local_1338 + 1] = (int)piVar6;
              local_131c.class_book[iVar3 + 3] = (int)piVar10;
              if (iVar3 == 1) {
                local_131c.partitionclass[2] = (int)piVar10;
              }
              pvVar8 = local_1334;
              iVar2 = local_132c;
              if ((-1 < (int)piVar5) || (-1 < (int)piVar6)) {
                while ((-1 < iVar1 + -1 && (local_131c.postlist[iVar1 + -0xd] == iVar3))) {
                  local_131c.postlist[iVar1 + -0xd] = local_1338;
                  iVar1 = iVar1 + -1;
                }
                iVar3 = *local_133c;
                while ((iVar3 + 1 < local_132c &&
                       (local_131c.class_subbook[6][iVar3 + 5] == local_1328))) {
                  local_131c.class_subbook[6][iVar3 + 5] = local_1338;
                  iVar3 = iVar3 + 1;
                }
              }
              goto LAB_005b3ee9;
            }
          }
          local_131c.partitionclass[local_1338 + 1] = -200;
          local_131c.class_book[local_1338 + 3] = -200;
          pvVar8 = local_1334;
          iVar2 = local_132c;
        }
LAB_005b3ee9:
        local_133c = local_133c + 1;
        local_1338 = local_1338 + 1;
      } while (local_1338 < iVar2);
    }
    iVar1 = local_131c.class_book[4];
    iVar3 = local_131c.partitionclass[1];
    local_133c = _vorbis_block_alloc(param_1,iVar2 * 4);
    piVar6 = (int *)iVar3;
    if ((-1 < local_131c.class_book[3]) && (piVar6 = (int *)local_131c.class_book[3], -1 < iVar3)) {
      piVar6 = (int *)(local_131c.class_book[3] + iVar3 >> 1);
    }
    *local_133c = (int)piVar6;
    piVar6 = (int *)local_131c.partitionclass[2];
    if ((-1 < iVar1) && (piVar6 = (int *)iVar1, -1 < local_131c.partitionclass[2])) {
      piVar6 = (int *)(local_131c.partitionclass[2] + iVar1 >> 1);
    }
    local_133c[1] = (int)piVar6;
    local_1338 = 2;
    if (2 < iVar2) {
      local_1330 = pvVar8->postlist + 2;
      piVar6 = param_2->hineighbor;
      do {
        uVar4 = (local_133c[*piVar6] & 0x7fffU) - (local_133c[piVar6[0x3f]] & 0x7fffU);
        iVar2 = (int)(((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)) *
                     (*local_1330 - local_1334->postlist[piVar6[0x3f]])) /
                (local_1334->postlist[*piVar6] - local_1334->postlist[piVar6[0x3f]]);
        if ((int)uVar4 < 0) {
          iVar2 = -iVar2;
        }
        uVar11 = (local_133c[piVar6[0x3f]] & 0x7fffU) + iVar2;
        uVar4 = local_131c.class_book[local_1338 + 3];
        if ((int)uVar4 < 0) {
          uVar4 = local_131c.partitionclass[local_1338 + 1];
        }
        else if (-1 < local_131c.partitionclass[local_1338 + 1]) {
          uVar4 = (int)(uVar4 + local_131c.partitionclass[local_1338 + 1]) >> 1;
        }
        if (((int)uVar4 < 0) || (uVar11 == uVar4)) {
          local_133c[local_1338] = uVar11 | 0x8000;
        }
        else {
          local_133c[local_1338] = uVar4;
        }
        local_1330 = local_1330 + 1;
        local_1338 = local_1338 + 1;
        piVar6 = piVar6 + 1;
      } while (local_1338 < local_132c);
    }
  }
  return local_133c;
}
