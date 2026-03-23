
undefined4
FUN_00698cd0(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,int param_7,
            int param_8)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint local_40;
  int local_3c;
  int local_38;
  int local_34;
  void *local_28;
  int local_20;
  int local_1c;
  int *local_18;
  int *local_14;
  int local_c;
  int local_8;
  
  iVar4 = param_8 + -1;
  if (param_4 == 0) {
    local_3c = iVar4;
    if (param_5 != 0) {
      local_3c = 0;
    }
    local_20 = local_3c;
  }
  else {
    local_38 = iVar4;
    if (param_5 == 0) {
      local_38 = 0;
    }
    local_20 = local_38;
  }
  if ((param_7 == DAT_02ceb810) && (param_8 == DAT_02ceb814)) {
    local_34 = DAT_02ceb818;
    local_28 = (void *)DAT_02ceb808;
    local_14 = DAT_02ceb804;
    local_18 = DAT_02ceb80c;
  }
  for (local_8 = 0; local_8 <= param_8 + 1; local_8 = local_8 + 1) {
    local_14[local_8] = local_20;
  }
  *local_18 = local_20;
  local_18[param_8 + 1] = local_20;
  for (local_1c = 0; local_1c <= param_7 + -1; local_1c = local_1c + 1) {
    piVar1 = local_18;
    *local_18 = local_20;
    for (local_8 = 0; local_8 < param_8; local_8 = local_8 + 1) {
      *(undefined4 *)((int)local_28 + local_8 * 4) =
           *(undefined4 *)(*(int *)(param_1 + local_1c * 4) + local_8 * 4);
      local_40 = (uint)(*(int *)((int)local_28 + local_8 * 4) != param_3);
      if (param_4 == local_40) {
        local_18[local_8 + 1] = 0;
      }
      else {
        local_c = local_18[local_8] + 1;
        if (local_14[local_8 + 1] + 1 < local_18[local_8] + 1) {
          local_c = local_14[local_8 + 1] + 1;
        }
        if (param_6 == 8) {
          if (local_14[local_8] + 1 < local_c) {
            local_c = local_14[local_8] + 1;
          }
          if (local_14[local_8 + 2] + 1 < local_c) {
            local_c = local_14[local_8 + 2] + 1;
          }
        }
        if (iVar4 < local_c) {
          local_c = iVar4;
        }
        local_18[local_8 + 1] = local_c;
      }
      *(int *)(*(int *)(local_34 + local_1c * 4) + local_8 * 4) = local_18[local_8 + 1];
    }
    local_18 = local_14;
    local_14 = piVar1;
  }
  for (local_8 = 0; piVar1 = local_18, piVar3 = local_14, local_1c = param_7, local_8 <= param_8;
      local_8 = local_8 + 1) {
    local_14[local_8] = local_20;
  }
  while (local_14 = piVar3, local_18 = piVar1, local_1c = local_1c + -1, -1 < local_1c) {
    iVar2 = param_8;
    while (local_8 = iVar2 + -1, piVar1 = local_14, piVar3 = local_18, -1 < local_8) {
      *(undefined4 *)((int)local_28 + local_8 * 4) =
           *(undefined4 *)(*(int *)(local_34 + local_1c * 4) + local_8 * 4);
      if (*(int *)((int)local_28 + local_8 * 4) == 0) {
        local_18[iVar2] = 0;
      }
      else {
        local_c = *(int *)((int)local_28 + local_8 * 4);
        if (local_18[iVar2 + 1] + 1 < local_c) {
          local_c = local_18[iVar2 + 1] + 1;
        }
        if (local_14[iVar2] + 1 < local_c) {
          local_c = local_14[iVar2] + 1;
        }
        if (param_6 == 8) {
          if (local_14[iVar2 + 1] + 1 < local_c) {
            local_c = local_14[iVar2 + 1] + 1;
          }
          if (local_14[local_8] + 1 < local_c) {
            local_c = local_14[local_8] + 1;
          }
        }
        if (iVar4 < local_c) {
          local_c = iVar4;
        }
        local_18[iVar2] = local_c;
      }
      *(int *)(*(int *)(param_2 + local_1c * 4) + local_8 * 4) = local_18[iVar2];
      iVar2 = local_8;
    }
  }
  if ((param_7 != DAT_02ceb810) || (param_8 != DAT_02ceb814)) {
    free(local_28);
    free(local_14);
    free(local_18);
    FUN_0069f010(local_34,0,param_7 + -1,0,param_8 + -1);
  }
  return 0;
}

