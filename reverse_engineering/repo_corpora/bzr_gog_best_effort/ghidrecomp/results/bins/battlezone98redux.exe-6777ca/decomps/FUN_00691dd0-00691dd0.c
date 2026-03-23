
undefined4
FUN_00691dd0(undefined4 param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  undefined4 local_14;
  uint local_c;
  uint local_8;
  
  FUN_006a5fd0("AIBuild_CanMineFitHere Begins\n");
  bVar1 = false;
  local_14 = 0;
  local_8 = 1;
  while (!bVar1) {
    local_c = 0;
    while ((local_c < local_8 && (!bVar1))) {
      iVar2 = FUN_00691d60(param_1,param_2,(param_3 - (local_8 >> 1)) + local_c,param_4 - local_8);
      if (iVar2 != 0) {
        bVar1 = true;
        local_14 = 1;
        *param_5 = (param_3 - (local_8 >> 1)) + local_c;
        *param_6 = param_4 - local_8;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar1))) {
      iVar2 = FUN_00691d60(param_1,param_2,(param_3 - (local_8 >> 1)) + local_c,param_4 + local_8);
      if (iVar2 != 0) {
        bVar1 = true;
        local_14 = 1;
        *param_5 = (param_3 - (local_8 >> 1)) + local_c;
        *param_6 = param_4 + local_8;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar1))) {
      iVar2 = FUN_00691d60(param_1,param_2,param_3 + local_8,(param_4 - (local_8 >> 1)) + local_c);
      if (iVar2 != 0) {
        bVar1 = true;
        local_14 = 1;
        *param_5 = param_3 + local_8;
        *param_6 = (param_4 - (local_8 >> 1)) + local_c;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar1))) {
      iVar2 = FUN_00691d60(param_1,param_2,param_3 - local_8,(param_4 - (local_8 >> 1)) + local_c);
      if (iVar2 != 0) {
        bVar1 = true;
        local_14 = 1;
        *param_5 = param_3 - local_8;
        *param_6 = (param_4 - (local_8 >> 1)) + local_c;
      }
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
    if (((*(uint *)(param_2 + 0x24) >> 0x12 & 0xf) >> 1 < local_8) ||
       ((*(uint *)(param_2 + 0x24) >> 0x16 & 0xf) >> 1 < local_8)) {
      bVar1 = true;
    }
  }
  FUN_006a5fd0("AIBuild_CanMineFitHere Ends\n");
  return local_14;
}

