
undefined4 FUN_0062a270(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 *local_34;
  undefined1 *local_30;
  undefined1 *local_2c;
  int local_28;
  undefined1 *local_24;
  int local_20;
  int local_1c;
  int local_18;
  
  *param_3 = -1;
  if (DAT_00920c58 < 0x200) {
    for (local_1c = 0; local_1c < DAT_00920c5c; local_1c = local_1c + 1) {
      iVar1 = *(int *)(&DAT_02a1b498 + local_1c * 4);
      if (((*(int *)(iVar1 + 0x38) == param_1) && (*(int *)(iVar1 + 0x3c) != 0)) &&
         (**(int **)(iVar1 + 0x3c) == param_1)) {
        local_20 = 0;
        while( true ) {
          if (*(int *)(iVar1 + 0x10) <= local_20) {
            if (param_2 != 2) {
              if (param_1 == 0) {
                local_30 = &DAT_00874be8;
              }
              else {
                local_30 = (undefined1 *)(param_1 + 8);
              }
              FUN_007d6c70("AnimObj_Start - requested obj %.8s has no animation at index %d\n",
                           local_30,param_2);
            }
            return 0xffffffff;
          }
          piVar3 = (int *)(local_20 * 0x94 + *(int *)(iVar1 + 0x24));
          if (*piVar3 == param_2) break;
          local_20 = local_20 + 1;
        }
        local_18 = 0;
        while( true ) {
          if (0x1ff < local_18) {
            if (param_1 == 0) {
              local_2c = &DAT_00874be8;
            }
            else {
              local_2c = (undefined1 *)(param_1 + 8);
            }
            FUN_007d6c70("AnimObj_Start - requested obj %.8s no empty slots in activelist\n",
                         local_2c);
            return 0xffffffff;
          }
          iVar2 = local_18 * 0x20;
          if (*(int *)(&DAT_02a17498 + iVar2) == 0) break;
          local_18 = local_18 + 1;
        }
        *(undefined1 *)(*(int *)(iVar1 + 0x3c) + 7) = 1;
        *(int *)(&DAT_02a17498 + iVar2) = 1;
        *(int *)(&DAT_02a1749c + iVar2) = iVar1;
        *(int *)(&DAT_02a174a0 + iVar2) = piVar3[0x24];
        *(int *)(&DAT_02a174a8 + iVar2) = piVar3[0x21];
        if (piVar3[0x22] < 1) {
          *(int *)(&DAT_02a174ac + iVar2) = piVar3[0x21] + 1 + piVar3[0x22];
          *(int *)(&DAT_02a174b0 + iVar2) = -piVar3[0x22];
        }
        else {
          *(int *)(&DAT_02a174ac + iVar2) = piVar3[0x21] + -1 + piVar3[0x22];
          *(int *)(&DAT_02a174b0 + iVar2) = piVar3[0x22];
        }
        *(float *)(&DAT_02a174a4 + iVar2) = (float)*(int *)(&DAT_02a174a8 + iVar2);
        if (piVar3[0x23] < 1) {
          local_28 = -1;
        }
        else {
          local_28 = piVar3[0x23] + -1;
        }
        *(int *)(&DAT_02a174b4 + iVar2) = local_28;
        *param_3 = local_18;
        DAT_00920c58 = DAT_00920c58 + 1;
        return 0;
      }
    }
    if (param_1 == 0) {
      local_34 = &DAT_00874be8;
    }
    else {
      local_34 = (undefined1 *)(param_1 + 8);
    }
    FUN_007d6c70("AnimObj_Start - requested obj %.8s is not in any animation\n",local_34);
  }
  else {
    if (param_1 == 0) {
      local_24 = &DAT_00874be8;
    }
    else {
      local_24 = (undefined1 *)(param_1 + 8);
    }
    FUN_007d6c70("AnimObj_Start - active anim list overflow, %.8s\n",local_24);
  }
  return 0xffffffff;
}

