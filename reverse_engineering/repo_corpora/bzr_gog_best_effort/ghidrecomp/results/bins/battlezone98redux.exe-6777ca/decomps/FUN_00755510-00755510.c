
void FUN_00755510(void)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined1 *puStack_d4;
  undefined4 uStack_cc;
  undefined1 *puStack_c8;
  undefined1 *puStack_c4;
  undefined1 *puStack_c0;
  uint uStack_bc;
  undefined1 local_b8 [8];
  undefined1 *local_b0;
  undefined1 local_ac [4];
  undefined1 local_a8 [4];
  undefined1 *local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  uint local_8c;
  undefined4 local_88;
  int local_84;
  undefined4 local_80;
  int *local_7c;
  int *local_78;
  int *local_74;
  int *local_70;
  uint local_6c;
  int local_68;
  undefined1 local_64 [8];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_4c [24];
  undefined1 local_34 [24];
  undefined1 local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c423;
  local_10 = ExceptionList;
  uStack_bc = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_c0 = (undefined1 *)0x755543;
  local_14 = uStack_bc;
  local_7c = (int *)FUN_0073ae00();
  puStack_c0 = (undefined1 *)0x755553;
  local_8c = (**(code **)(*local_7c + 0x3c))();
  puStack_c0 = (undefined1 *)0x755564;
  FUN_00755c70();
  for (local_6c = 0; local_6c < local_8c; local_6c = local_6c + 1) {
    puStack_c0 = (undefined1 *)0x75558d;
    FUN_00753840();
    local_8 = 0;
    puStack_c0 = (undefined1 *)0x755599;
    local_70 = (int *)FUN_0073ae00();
    puStack_c0 = (undefined1 *)local_6c;
    puStack_c4 = local_b8;
    puStack_c8 = (undefined1 *)0x7555b4;
    puStack_c8 = (undefined1 *)(**(code **)(*local_70 + 0x40))();
    uStack_cc = 0x7555c0;
    FUN_0073a710();
    local_5c = local_a0;
    local_58 = local_9c;
    local_54 = local_98;
    local_50 = local_94;
    puStack_c8 = (undefined1 *)0x7555e9;
    local_78 = (int *)FUN_0073ae00();
    local_b0 = (undefined1 *)&uStack_cc;
    puStack_d4 = (undefined1 *)0x755600;
    FUN_0073a9b0();
    pcVar1 = (char *)(**(code **)(*local_78 + 0x14))();
    puStack_d4 = (undefined1 *)0x755616;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_4c,pcVar1);
    puStack_d4 = (undefined1 *)0x755622;
    FID_conflict_operator_();
    local_88 = FUN_006ab6b0();
    local_8._0_1_ = 1;
    puStack_d4 = local_34;
    local_80 = local_88;
    FUN_00756750();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417b50();
    local_1c = 0;
    local_74 = (int *)FUN_0073ae00();
    local_a4 = (undefined1 *)&puStack_d4;
    FUN_0073a9b0(&puStack_d4);
    local_84 = (**(code **)(*local_74 + 0x1c))();
    if (local_84 == 1) {
      puStack_c0 = local_64;
      puStack_c4 = (undefined1 *)0x7556a4;
      FUN_00755b60();
    }
    local_8 = 0xffffffff;
    puStack_c0 = (undefined1 *)0x7556b3;
    FUN_007538f0();
  }
  puStack_c0 = (undefined1 *)(uint)*(byte *)(local_68 + -0x1c);
  puStack_c4 = local_ac;
  puStack_c8 = (undefined1 *)0x7556d2;
  puVar2 = (undefined4 *)FID_conflict_end();
  puStack_c4 = (undefined1 *)*puVar2;
  puStack_c8 = local_a8;
  uStack_cc = 0x7556e7;
  puVar2 = (undefined4 *)FID_conflict_begin();
  puStack_c8 = (undefined1 *)*puVar2;
  uStack_cc = 0x7556ef;
  FUN_00756790();
  puStack_c0 = (undefined1 *)0x7556f7;
  FUN_0078a770();
  ExceptionList = local_10;
  uStack_bc = 0x75570c;
  FUN_0083e885();
  return;
}

