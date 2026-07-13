
undefined4 * FUN_006e8a10(undefined4 *param_1)

{
  char cVar1;
  undefined4 uStack_c8;
  undefined1 *puStack_c0;
  undefined4 *puStack_b8;
  undefined1 local_ac [16];
  undefined1 local_9c [8];
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_84;
  undefined1 *local_78;
  undefined4 local_74;
  undefined1 *local_70;
  undefined1 *local_6c;
  undefined1 *local_68;
  undefined1 *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  code *local_48;
  undefined4 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int *local_30;
  undefined4 local_28;
  undefined4 local_24;
  shared_ptr<class___ExceptionPtr> local_20 [11];
  char local_15;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085484e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_b8 = (undefined4 *)0x6e8a55;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    puStack_b8 = (undefined4 *)0x400;
    FUN_006d08b0();
  }
  puStack_b8 = (undefined4 *)0x6e8a85;
  FUN_006d1110();
  local_8._0_1_ = 1;
  if (*(int *)(local_14 + 0xa20) != 1) {
    puStack_b8 = param_1;
    make_error_code();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006d1140();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
    ExceptionList = local_10;
    return param_1;
  }
  local_8._0_1_ = 0;
  FUN_006d1140();
  FUN_0068b0a0();
  local_8._0_1_ = 2;
  local_15 = 0;
  FUN_00421ec0();
  cVar1 = FUN_006f2d70();
  if (cVar1 == '\0') {
    puStack_b8 = (undefined4 *)0x6e8b96;
    FUN_00421ec0();
    puStack_b8 = (undefined4 *)0x6e8b9d;
    local_50 = FUN_006e1ae0();
    puStack_b8 = (undefined4 *)0x6e8bac;
    FID_conflict_operator_();
    FUN_006ca8c0();
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      puStack_b8 = param_1;
      make_error_code();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      FUN_006ca8c0();
      ExceptionList = local_10;
      return param_1;
    }
    puStack_b8 = (undefined4 *)0x6e8c05;
    FUN_006d1110();
    local_8._0_1_ = 4;
    local_30 = (int *)FUN_00421ec0();
    local_6c = (undefined1 *)&puStack_b8;
    puStack_c0 = (undefined1 *)0x6e8c2b;
    local_74 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_b8,local_20);
    local_68 = (undefined1 *)&puStack_c0;
    uStack_c8 = 0x6e8c3f;
    local_84 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_c0,
                          (shared_ptr<class___ExceptionPtr> *)&stack0x00000008);
    uStack_c8 = 0x6e8c53;
    (**(code **)(*local_30 + 0x48))();
    cVar1 = FUN_006ab7d0();
    if (cVar1 != '\0') {
      *param_1 = local_5c;
      param_1[1] = local_58;
      local_8._0_1_ = 2;
      FUN_006d1140();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      FUN_006ca8c0();
      ExceptionList = local_10;
      return param_1;
    }
    local_70 = (undefined1 *)&puStack_b8;
    puStack_c0 = (undefined1 *)0x6e8cb0;
    local_94 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_b8,local_20);
    FUN_006ea380();
    if ((*(char *)(local_14 + 0x4ab8) == '\0') && (cVar1 = FUN_006e1c30(), cVar1 == '\0')) {
      local_28 = 1;
    }
    else {
      local_28 = 0;
    }
    local_15 = (char)local_28;
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_006d1140();
  }
  else {
    puStack_b8 = (undefined4 *)0x6e8b08;
    std::shared_ptr<class___ExceptionPtr>::operator=
              (local_20,(shared_ptr<class___ExceptionPtr> *)&stack0x00000008);
    puStack_b8 = (undefined4 *)0x6e8b1a;
    FUN_006d1110();
    local_8 = CONCAT31(local_8._1_3_,3);
    local_64 = (undefined1 *)&puStack_b8;
    puStack_c0 = (undefined1 *)0x6e8b2f;
    local_60 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                         ((shared_ptr<class___ExceptionPtr> *)&puStack_b8,local_20);
    FUN_006ea380();
    if ((*(char *)(local_14 + 0x4ab8) == '\0') && (cVar1 = FUN_006e1c30(), cVar1 == '\0')) {
      local_24 = 1;
    }
    else {
      local_24 = 0;
    }
    local_15 = (char)local_24;
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_006d1140();
  }
  if (local_15 != '\0') {
    local_48 = FUN_006e9190;
    local_44 = (undefined4 *)0x0;
    puStack_b8 = (undefined4 *)0x6e8d2c;
    local_54 = FUN_006e1540();
    local_8._0_1_ = 5;
    puStack_b8 = local_44;
    puStack_c0 = local_ac;
    local_40 = local_54;
    local_4c = FUN_006eabe0();
    local_8._0_1_ = 6;
    local_78 = (undefined1 *)&uStack_c8;
    local_3c = local_4c;
    local_90 = FUN_006eac20(local_4c);
    FUN_006e1210(local_9c);
    local_8._0_1_ = 5;
    ~<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_006ca8c0();
  }
  FUN_006ab750();
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

