
undefined4 FUN_00692200(undefined4 *param_1,undefined2 param_2,int *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 local_1c;
  int local_c;
  int local_8;
  
  FUN_006a5fd0("AIBuild_FindNormalFacilityLocation Begins\n");
  uVar4 = FUN_006a0670(param_2);
  uVar6 = *param_1;
  iVar1 = param_1[0x91];
  iVar2 = param_1[0x92];
  bVar3 = false;
  local_1c = 0;
  local_8 = 1;
  while (!bVar3) {
    local_c = 0;
    while ((local_c < local_8 && (!bVar3))) {
      iVar5 = FUN_00692150(param_1,0,uVar4,(iVar1 - local_8 / 2) + local_c,iVar2 - local_8);
      if (iVar5 != 0) {
        bVar3 = true;
        local_1c = 1;
        *param_3 = (iVar1 - local_8 / 2) + local_c;
        *param_4 = iVar2 - local_8;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar3))) {
      iVar5 = FUN_00692150(param_1,0,uVar4,(iVar1 - local_8 / 2) + local_c,iVar2 + local_8);
      if (iVar5 != 0) {
        bVar3 = true;
        local_1c = 1;
        *param_3 = (iVar1 - local_8 / 2) + local_c;
        *param_4 = iVar2 + local_8;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar3))) {
      iVar5 = FUN_00692150(param_1,0,uVar4,iVar1 + local_8,(iVar2 - local_8 / 2) + local_c);
      if (iVar5 != 0) {
        bVar3 = true;
        local_1c = 1;
        *param_3 = iVar1 + local_8;
        *param_4 = (iVar2 - local_8 / 2) + local_c;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    while ((local_c < local_8 && (!bVar3))) {
      iVar5 = FUN_00692150(param_1,0,uVar4,iVar1 - local_8,(iVar2 - local_8 / 2) + local_c);
      if (iVar5 != 0) {
        bVar3 = true;
        local_1c = 1;
        *param_3 = iVar1 - local_8;
        *param_4 = (iVar2 - local_8 / 2) + local_c;
      }
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
    if ((DAT_008eda24 < local_8) && (DAT_008eda20 < local_8)) {
      bVar3 = true;
    }
  }
  FUN_006a5fd0("AIBuild_FindNormalFacilityLocation Ends\n",uVar6);
  return local_1c;
}

