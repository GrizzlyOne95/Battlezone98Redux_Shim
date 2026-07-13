/*
 * Entry: 005109a8
 * Name: Grassfire_Xform
 * Namespace: Global
 * Signature: int Grassfire_Xform(int * * param_1, int * * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Grassfire_Xform(int **param_1,int **param_2,int param_3,int param_4,int param_5,int param_6,
               int param_7,int param_8)

{
  uint uVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint *puVar13;
  int local_28;
  int *local_24;
  int **local_1c;
  int **local_18;
  int local_14;
  uint *local_10;
  uint *local_8;
  
  Debug_Assert(grassfire_initialised,0x7a,".\\Schedule\\Grasfire.c","grassfire_initialised");
  uVar1 = param_8 - 1;
  if (param_4 == 0) {
    uVar10 = ~-(uint)(param_5 != 0);
  }
  else {
    uVar10 = -(uint)(param_5 != 0);
  }
  uVar10 = uVar10 & uVar1;
  if ((param_7 == default_rows) && (param_8 == default_columns)) {
    local_1c = default_temp;
    local_24 = default_inbuf;
    local_8 = (uint *)default_this_one;
    puVar4 = (uint *)default_other;
  }
  else {
    Debug_Assert(0,0x8a,".\\Schedule\\Grasfire.c","1 == 0");
    puVar4 = (uint *)param_8;
  }
  Debug_Assert((int)local_8,0xac,".\\Schedule\\Grasfire.c","this_one");
  Debug_Assert((int)puVar4,0xad,".\\Schedule\\Grasfire.c","other");
  iVar8 = param_8 + 1;
  if (-1 < iVar8) {
    puVar13 = local_8;
    for (iVar5 = param_8 + 2; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar13 = uVar10;
      puVar13 = puVar13 + 1;
    }
  }
  iVar5 = param_7 + -1;
  *puVar4 = uVar10;
  puVar4[param_8 + 1] = uVar10;
  if (-1 < iVar5) {
    local_18 = local_1c;
    local_28 = param_7;
    iVar9 = -(int)puVar4;
    iVar12 = -(int)local_8;
    do {
      puVar13 = puVar4;
      iVar6 = iVar9;
      local_14 = 0;
      *puVar13 = uVar10;
      if (0 < param_8) {
        puVar4 = local_8 + 2;
        puVar3 = puVar13;
        do {
          local_10 = puVar3 + 1;
          iVar9 = *(int *)((int)puVar4 +
                          *(int *)(((int)param_1 - (int)local_1c) + (int)local_18) + iVar12 + -8);
          local_24[local_14] = iVar9;
          if (param_4 == (uint)(iVar9 != param_3)) {
            *local_10 = 0;
          }
          else {
            uVar7 = *puVar3 + 1;
            if ((int)(puVar4[-1] + 1) < (int)(*puVar3 + 1)) {
              uVar7 = puVar4[-1] + 1;
            }
            if (param_6 == 8) {
              if ((int)(puVar4[-2] + 1) < (int)uVar7) {
                uVar7 = puVar4[-2] + 1;
              }
              if ((int)(*puVar4 + 1) < (int)uVar7) {
                uVar7 = *puVar4 + 1;
              }
            }
            if ((int)uVar1 < (int)uVar7) {
              uVar7 = uVar1;
            }
            *local_10 = uVar7;
          }
          local_14 = local_14 + 1;
          *(uint *)(iVar12 + -8 + (int)puVar4 + (int)*local_18) = *local_10;
          puVar4 = puVar4 + 1;
          puVar3 = local_10;
        } while (local_14 < param_8);
      }
      local_18 = local_18 + 1;
      local_28 = local_28 + -1;
      iVar9 = iVar12;
      puVar4 = local_8;
      iVar12 = iVar6;
      local_8 = puVar13;
    } while (local_28 != 0);
  }
  puVar13 = local_8;
  if (-1 < param_8) {
    for (; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar13 = uVar10;
      puVar13 = puVar13 + 1;
    }
  }
  if (-1 < iVar5) {
    local_18 = param_2 + iVar5;
    iVar8 = -(int)local_8;
    iVar9 = -(int)puVar4;
    local_14 = iVar5;
    do {
      puVar13 = puVar4;
      iVar12 = iVar8;
      if (-1 < (int)uVar1) {
        param_4 = (int)(puVar13 + param_8);
        puVar4 = local_8 + param_8 + 1;
        uVar10 = uVar1;
        do {
          iVar8 = (int)puVar4 + iVar12 + -8;
          uVar7 = *(uint *)(iVar8 + *(int *)(((int)local_1c - (int)param_2) + (int)local_18));
          local_24[uVar10] = uVar7;
          if (uVar7 == 0) {
            *(undefined4 *)param_4 = 0;
          }
          else {
            uVar11 = *(int *)((int)puVar4 + ((int)puVar13 - (int)local_8)) + 1;
            if ((int)uVar11 < (int)uVar7) {
              uVar7 = uVar11;
            }
            if ((int)(puVar4[-1] + 1) < (int)uVar7) {
              uVar7 = puVar4[-1] + 1;
            }
            if (param_6 == 8) {
              if ((int)(*puVar4 + 1) < (int)uVar7) {
                uVar7 = *puVar4 + 1;
              }
              if ((int)(puVar4[-2] + 1) < (int)uVar7) {
                uVar7 = puVar4[-2] + 1;
              }
            }
            if ((int)uVar1 < (int)uVar7) {
              uVar7 = uVar1;
            }
            *(uint *)param_4 = uVar7;
          }
          uVar2 = *(undefined4 *)param_4;
          param_4 = param_4 + -4;
          uVar10 = uVar10 - 1;
          puVar4 = puVar4 + -1;
          *(undefined4 *)(iVar8 + (int)*local_18) = uVar2;
        } while (-1 < (int)uVar10);
      }
      local_14 = local_14 + -1;
      local_18 = local_18 + -1;
      iVar8 = iVar9;
      iVar9 = iVar12;
      puVar4 = local_8;
      local_8 = puVar13;
    } while (-1 < local_14);
  }
  if ((param_7 != default_rows) || (param_8 != default_columns)) {
    Debug_Assert(0,0x105,".\\Schedule\\Grasfire.c","1 == 0");
    free(local_24);
    free(local_8);
    free(puVar4);
    NR_Free_Imatrix(local_1c,0,iVar5,0,uVar1);
  }
  return 0;
}
