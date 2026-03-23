
int * FUN_0041dd20(undefined4 param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int local_114 [44];
  int *local_64;
  int *local_60;
  int *local_5c;
  int *local_58;
  int *local_54;
  void *local_50;
  int local_4c;
  int local_48;
  void *local_44;
  int *local_40;
  void *local_3c;
  void *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  int local_28;
  float local_24;
  int local_20;
  undefined1 local_19;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844f99;
  local_10 = ExceptionList;
  local_14 = (int *)0x0;
  local_18 = (int *)0x0;
  if (*(int *)(param_2 + 0x18) == 1) {
    local_18 = (int *)0x0;
  }
  else if (*(int *)(param_2 + 0x18) == 2) {
    ExceptionList = &local_10;
    uVar2 = FUN_0041f870(0,0,0,0,0);
    local_28 = FUN_006218c0(uVar2);
    if (local_28 != 0) {
      *(int *)(local_20 + 0xc) = local_28;
      *(byte *)(local_20 + 0x10) = (byte)*(undefined4 *)(param_2 + 0x44) & 1;
      if ((*(uint *)(param_2 + 0x44) & 2) == 0) {
        FUN_0041fe40(&local_28);
      }
    }
    if (((*(uint *)(param_2 + 0x44) & 2) == 0) && (local_28 != 0)) {
      FUN_0041fe40(&local_28);
    }
    local_18 = (int *)0x0;
  }
  else if (*(int *)(param_2 + 0x18) == 9) {
    local_4c = 1;
    ExceptionList = &local_10;
    uVar2 = FUN_0041f870(&local_4c,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_48 = FUN_00621950(uVar2);
    if ((local_48 != 0) && (local_4c == 0)) {
      FUN_0041fe40(&local_48);
    }
    local_18 = (int *)0x0;
  }
  else {
    if (*(int *)(param_2 + 0x18) == 10) {
      if (param_3 != 0) {
        return (int *)0x0;
      }
      ExceptionList = &local_10;
      local_3c = operator_new(0x128);
      local_8 = 0;
      if (local_3c == (void *)0x0) {
        local_30 = (int *)0x0;
      }
      else {
        local_30 = (int *)FUN_0041a4b0(param_1,param_2 + 0x2c,*(undefined4 *)(param_2 + 0x44),
                                       param_2 + 0x48,*(undefined4 *)(param_2 + 0x60));
      }
      local_58 = local_30;
      local_8 = 0xffffffff;
      local_2c = local_30;
      FUN_0041a6b0(local_20 + 0x20);
      FUN_0041fe40(&local_2c);
      local_14 = local_2c;
    }
    else if (*(int *)(param_2 + 0x18) == 5) {
      if (param_3 != 0) {
        return (int *)0x0;
      }
      ExceptionList = &local_10;
      FUN_004203f0(param_2 + 0x2c,3,1);
      local_8._0_1_ = 1;
      local_8._1_3_ = 0;
      std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                ((basic_istream<char,struct_std::char_traits<char>_> *)local_114,&local_24);
      bVar1 = std::ios_base::operator!((ios_base *)((int)local_114 + *(int *)(local_114[0] + 4)));
      if ((bVar1) || (local_24 <= 30.0)) {
        local_24 = 120.0;
      }
      if (180.0 < local_24) {
        local_24 = 180.0;
      }
      if ((DAT_02cc2da8 & 1) == 0) {
        DAT_02cc2da8 = DAT_02cc2da8 | 1;
        local_8._0_1_ = 2;
        basic_string<>("Close");
        FUN_0083e979(FUN_00865fd0);
        local_8._0_1_ = 1;
      }
      local_44 = operator_new(0xb4);
      local_8 = CONCAT31(local_8._1_3_,3);
      if (local_44 == (void *)0x0) {
        local_54 = (int *)0x0;
      }
      else {
        local_54 = (int *)FUN_0041ad40(param_1,param_2 + 0x2c,0,local_24,param_2 + 0x68,
                                       &DAT_02cc2df4);
      }
      local_64 = local_54;
      local_18 = local_54;
      local_14 = local_54;
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else if (*(int *)(param_2 + 0x18) == 4) {
      ExceptionList = &local_10;
      local_50 = operator_new(0xac);
      local_8 = 4;
      if (local_50 == (void *)0x0) {
        local_34 = (int *)0x0;
      }
      else {
        local_34 = (int *)FUN_0041bca0(param_1,param_2,param_3);
      }
      local_5c = local_34;
      local_8 = 0xffffffff;
      local_18 = local_34;
      local_14 = local_34;
    }
    else {
      ExceptionList = &local_10;
      local_38 = operator_new(0xa8);
      local_8 = 5;
      if (local_38 == (void *)0x0) {
        local_40 = (int *)0x0;
      }
      else {
        local_40 = (int *)FUN_0041b7b0(param_1,param_2,param_3);
      }
      local_60 = local_40;
      local_8 = 0xffffffff;
      local_18 = local_40;
      local_14 = local_40;
    }
    if (local_18 != (int *)0x0) {
      FUN_0041fe40(&local_18);
    }
    if (param_3 != 0) {
      FUN_0041b370(local_18);
    }
    FUN_00418f30(1);
    if ((*(uint *)(param_2 + 0x44) & 8) == 0) {
      if ((*(uint *)(param_2 + 0x44) & 0x10) == 0) {
        if ((*(uint *)(param_2 + 0x44) & 0x20) == 0) {
          FUN_00418f10(0);
        }
        else {
          FUN_00418f10(2);
        }
      }
      else {
        FUN_00418f10(1);
      }
    }
    else {
      FUN_00418f10(0);
    }
    local_14[0x1d] = *(int *)(param_2 + 0x80);
    local_14[0x1e] = *(int *)(param_2 + 0x84);
    if (((*(uint *)(param_2 + 0x44) & 4) == 0) || (iVar3 = FUN_0041c1d0(), iVar3 != 0)) {
      local_19 = 0;
    }
    else {
      local_19 = 1;
    }
    (**(code **)(*local_14 + 4))(param_2 + 0x1c,local_19);
    if ((local_18 != (int *)0x0) && ((*(uint *)(param_2 + 0x44) & 0x40) != 0)) {
      FUN_0041fe40(&local_18);
      *(undefined1 *)(local_18 + 0x1c) = 1;
    }
  }
  ExceptionList = local_10;
  return local_18;
}

