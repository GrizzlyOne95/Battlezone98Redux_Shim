
int FUN_00426e30(undefined4 param_1,int param_2,int param_3,int param_4,char param_5,char param_6)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_d4 [16];
  undefined1 local_c4 [20];
  undefined1 local_b0 [12];
  undefined1 local_a4 [12];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  int local_84;
  undefined1 local_7c [4];
  undefined1 local_78 [4];
  int local_74;
  undefined1 local_6c [4];
  undefined4 local_68 [4];
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  int local_3c;
  int local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  char local_21;
  int local_20;
  undefined4 local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845503;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_11 = '\0';
  if (((param_6 != '\0') && (param_4 != 0)) && (local_20 = FUN_0042a7f0(&param_4), local_20 < 0)) {
    ExceptionList = local_10;
    return local_20;
  }
  FUN_004282e0(param_1,0);
  FUN_00428360(&local_2c,local_a4);
  uVar2 = FID_conflict_begin(local_8c);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    if ((param_6 != '\0') && (local_20 = FUN_0042a7f0(&param_1), local_20 < 0)) {
      ExceptionList = local_10;
      return local_20;
    }
    local_44 = *(int *)(local_18 + 0x20) + 1;
    *(int *)(local_18 + 0x20) = local_44;
    FUN_004282e0(param_1,local_44);
    if ((param_4 != 0) && ((param_2 == 0 || (param_3 == 0)))) {
      local_74 = param_4;
    }
    local_50 = FUN_00428520();
    local_8 = 0;
    local_4c = local_50;
    FUN_0042a9c0(local_78,local_50);
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_00428210();
    FUN_0042aa00(local_68,local_c4);
    local_2c = local_68[0];
    local_11 = '\x01';
    local_8 = 0xffffffff;
    what();
  }
  if ((param_2 == 0) || (param_3 == 0)) {
    if (local_11 != '\0') {
      ExceptionList = local_10;
      return 2;
    }
    ExceptionList = local_10;
    return 1;
  }
  local_28 = FUN_00422150();
  local_28 = local_28 + 0xc;
  FUN_004282e0(param_2,0);
  FUN_00428360(&local_1c,local_b0);
  local_3c = *(int *)(local_18 + 0x20) + 1;
  *(int *)(local_18 + 0x20) = local_3c;
  local_34 = local_3c;
  uVar2 = FID_conflict_begin(local_98);
  cVar1 = FUN_00420f10(uVar2);
  if (((cVar1 != '\0') && (*(char *)(local_18 + 0x1d) != '\0')) && (param_5 != '\0')) {
    local_30 = 0;
    while( true ) {
      uVar2 = FID_conflict_begin(local_6c);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00422150();
      cVar1 = FUN_004282a0(param_2,*puVar3);
      if (cVar1 != '\0') break;
      iVar4 = FUN_00422150();
      if (*(int *)(iVar4 + 8) < local_34) {
        iVar4 = FUN_00422150();
        local_34 = *(int *)(iVar4 + 8);
        iVar4 = FUN_00422150();
        local_30 = *(int *)(iVar4 + 4);
      }
      FUN_00428570();
    }
    if (local_30 != 0) {
      FUN_0042a910(param_4);
      param_4 = local_30;
      FUN_0042a7f0(&param_4);
    }
    FUN_0042a7c0(param_1,param_2,0);
    puVar3 = (undefined4 *)FID_conflict_begin(local_94);
    local_1c = *puVar3;
  }
  if ((*(char *)(local_18 + 0x1d) == '\0') || (param_5 != '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  local_21 = (char)local_40;
  if (param_6 == '\0') goto LAB_004271a9;
  if ((char)local_40 == '\0') {
    uVar2 = FID_conflict_begin(local_7c);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 != '\0') goto LAB_0042716f;
  }
  else {
LAB_0042716f:
    local_20 = FUN_0042a7f0(&param_2);
    if (local_20 < 0) {
      ExceptionList = local_10;
      return local_20;
    }
  }
  local_20 = FUN_0042a7f0(&param_3);
  if (local_20 < 0) {
    ExceptionList = local_10;
    return local_20;
  }
LAB_004271a9:
  uVar2 = FID_conflict_begin(local_90);
  cVar1 = FUN_004221b0(uVar2);
  if ((cVar1 != '\0') || (local_21 != '\0')) {
    FUN_004282e0(param_2,local_34);
    if (param_4 != 0) {
      local_84 = param_4;
    }
    local_54 = 0;
    FUN_0042aa50(local_88,&local_54);
    puVar3 = (undefined4 *)FUN_0042aa90(local_58,local_d4);
    local_1c = *puVar3;
    local_11 = '\x01';
  }
  iVar4 = FUN_00422150();
  *(int *)(iVar4 + 0xc) = param_3;
  if (local_11 == '\0') {
    local_48 = 1;
  }
  else {
    local_48 = 2;
  }
  ExceptionList = local_10;
  return local_48;
}

