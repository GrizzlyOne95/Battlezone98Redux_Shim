
void FUN_006da770(char *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 *puVar3;
  undefined1 *puStack_200;
  code *pcStack_1fc;
  undefined1 *puStack_1f8;
  char *pcStack_1f0;
  int iVar4;
  undefined1 auStack_1d4 [160];
  undefined1 local_134 [8];
  undefined1 local_12c [16];
  char local_11c [8];
  undefined1 local_114 [16];
  char local_104 [8];
  undefined1 *local_fc;
  undefined4 local_f8;
  undefined1 *local_f4;
  undefined1 *local_f0;
  undefined1 *local_e4;
  undefined4 local_d8;
  undefined1 local_d4 [8];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  code *local_bc;
  char *local_b8;
  undefined4 local_b4;
  code *local_b0;
  undefined1 *local_ac;
  undefined4 local_a8;
  undefined4 *local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined1 *local_74;
  int *local_70;
  shared_ptr<class___ExceptionPtr> local_6c [11];
  char local_61;
  int local_60;
  undefined1 local_5c [72];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008538c7;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_1f0 = (char *)0x6da7b1;
  cVar2 = FUN_006d4590();
  if (cVar2 != '\0') {
    pcStack_1f0 = (char *)0x400;
    FUN_006d08b0();
  }
  pcStack_1f0 = (char *)0x6da7e1;
  FUN_006d1110();
  local_8 = 0;
  if (*(int *)(local_60 + 0xa20) != 1) {
    pcStack_1f0 = (char *)0x3;
    FUN_00574400();
    local_8._0_1_ = 1;
    if (&stack0x00000000 == (undefined1 *)0x1e4) {
      local_74 = (undefined1 *)0x0;
    }
    else {
      local_74 = auStack_1d4;
    }
    iVar4 = *(int *)(local_60 + 0xa20);
    pcStack_1f0 = "connection::ping called from invalid state ";
    puStack_1f8 = (undefined1 *)0x6da842;
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pcStack_1f0 = (char *)0x6da84d;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar4);
    pcStack_1f0 = (char *)0x6da85c;
    local_9c = GetPolicy();
    local_8._0_1_ = 2;
    pcStack_1f0 = (char *)0x400;
    local_90 = local_9c;
    FUN_006d4480();
    local_8._0_1_ = 1;
    ~basic_string<>();
    pcStack_1f0 = local_104;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_006d1140();
    goto LAB_006dacae;
  }
  local_8 = 0xffffffff;
  FUN_006d1140();
  pcStack_1f0 = (char *)0x6da8fa;
  FUN_00421ec0();
  pcStack_1f0 = (char *)0x6da901;
  FUN_006e1ae0();
  local_8 = 3;
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    pcStack_1f0 = local_11c;
    puVar3 = (undefined4 *)make_error_code();
    uVar1 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_006dacae;
  }
  local_70 = (int *)FUN_00421ec0();
  local_f0 = (undefined1 *)&pcStack_1f0;
  puStack_1f8 = (undefined1 *)0x6da96e;
  local_c8 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_1f0,local_6c);
  puStack_1f8 = local_12c;
  pcStack_1fc = (code *)0x6da98c;
  local_a4 = (undefined4 *)(**(code **)(*local_70 + 0x4c))();
  uVar1 = local_a4[1];
  *param_2 = *local_a4;
  param_2[1] = uVar1;
  cVar2 = FUN_006ab7d0();
  if (cVar2 != '\0') {
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    goto LAB_006dacae;
  }
  cVar2 = FUN_006caba0();
  if (cVar2 != '\0') {
    cVar2 = FUN_006ab7d0();
    if (cVar2 != '\0') {
      FUN_00421ec0();
      FUN_006d70d0();
    }
    if (0 < *(int *)(local_60 + 0xa18)) {
      local_b0 = FUN_006e8de0;
      local_ac = (undefined1 *)0x0;
      pcStack_1f0 = (char *)0x6daa3e;
      local_c4 = FUN_006e1540();
      local_8._0_1_ = 4;
      pcStack_1f0 = param_1;
      puStack_1f8 = local_ac;
      pcStack_1fc = local_b0;
      puStack_200 = local_5c;
      local_88 = local_c4;
      local_b4 = FUN_006eab10();
      local_8._0_1_ = 5;
      local_e4 = (undefined1 *)&puStack_200;
      local_80 = local_b4;
      local_cc = FUN_006eab70(local_b4);
      local_a8 = FUN_006d4050(local_d4,*(undefined4 *)(local_60 + 0xa18));
      pcStack_1f0 = (char *)0x6daaed;
      local_98 = local_a8;
      FID_conflict_operator_();
      FUN_006ca8c0();
      local_8._0_1_ = 4;
      FUN_006dfcb0();
      local_8 = CONCAT31(local_8._1_3_,3);
      FUN_006ca8c0();
    }
    cVar2 = FUN_006ab7d0();
    if (cVar2 == '\0') {
      pcStack_1f0 = (char *)0x8;
      FUN_006d47b0();
    }
  }
  local_61 = 0;
  pcStack_1f0 = (char *)0x6dab56;
  FUN_006d1110();
  local_8 = CONCAT31(local_8._1_3_,6);
  local_fc = (undefined1 *)&pcStack_1f0;
  puStack_1f8 = (undefined1 *)0x6dab6e;
  local_f8 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_1f0,local_6c);
  FUN_006ea380();
  if (*(char *)(local_60 + 0x4ab8) == '\0') {
    cVar2 = FUN_006e1c30();
    if (cVar2 != '\0') goto LAB_006daba8;
    local_7c = 1;
  }
  else {
LAB_006daba8:
    local_7c = 0;
  }
  local_61 = (char)local_7c;
  local_8._0_1_ = 3;
  FUN_006d1140();
  if (local_61 != '\0') {
    local_bc = FUN_006e9190;
    local_b8 = (char *)0x0;
    pcStack_1f0 = (char *)0x6dabf3;
    local_a0 = FUN_006e1540();
    local_8._0_1_ = 7;
    pcStack_1f0 = local_b8;
    puStack_1f8 = local_114;
    pcStack_1fc = (code *)0x6dac24;
    local_84 = local_a0;
    local_94 = FUN_006eabe0();
    local_8._0_1_ = 8;
    local_f4 = (undefined1 *)&puStack_200;
    local_8c = local_94;
    local_d8 = FUN_006eac20(local_94);
    FUN_006e1210(local_134);
    local_8._0_1_ = 7;
    ~<>();
    local_8._0_1_ = 3;
    FUN_006ca8c0();
  }
  puVar3 = (undefined4 *)FUN_006ab750();
  uVar1 = puVar3[1];
  *param_2 = *puVar3;
  param_2[1] = uVar1;
  local_8 = 0xffffffff;
  FUN_006ca8c0();
LAB_006dacae:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

