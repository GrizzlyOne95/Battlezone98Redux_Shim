
void FUN_00758010(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char *pcVar3;
  uint uVar4;
  undefined1 local_c0 [8];
  undefined1 local_b8 [8];
  undefined1 local_b0 [8];
  undefined1 local_a8 [4];
  undefined1 local_a4 [4];
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  int local_8c;
  undefined4 local_84;
  int *local_80;
  int *local_7c;
  int *local_78;
  int *local_74;
  int local_70;
  int local_6c;
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
  puStack_c = &LAB_0085c6c3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_74 = (int *)FUN_006aa1d0(local_14);
  local_8c = (**(code **)(*local_74 + 0xc))(4);
  FUN_00755c70();
  for (local_70 = 0; local_70 < local_8c; local_70 = local_70 + 1) {
    FUN_00753840();
    local_8 = 0;
    local_80 = (int *)FUN_006aa1d0();
    uVar1 = (**(code **)(*local_80 + 0x10))(local_b0,local_70,4);
    FUN_0073a6e0(uVar1);
    local_5c = local_a0;
    local_58 = local_9c;
    local_54 = local_98;
    local_50 = local_94;
    local_7c = (int *)FUN_006aa1d0();
    puVar2 = (undefined4 *)FUN_0073a970(local_b8);
    pcVar3 = (char *)(**(code **)(*local_7c + 0x1c))(*puVar2,puVar2[1]);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_4c,pcVar3);
    FID_conflict_operator_(local_4c);
    local_90 = FUN_006ab6b0();
    local_8._0_1_ = 1;
    local_84 = local_90;
    FUN_00756750(local_34,local_90);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417b50();
    local_1c = 0;
    local_78 = (int *)FUN_006aa1d0();
    puVar2 = (undefined4 *)FUN_0073a970(local_c0);
    local_68 = (**(code **)(*local_78 + 0x18))(*puVar2,puVar2[1]);
    if ((((local_68 == 1) || (local_68 == 2)) || (local_68 == 3)) ||
       (((local_68 == 4 || (local_68 == 5)) || (local_68 == 6)))) {
      FUN_00755b60(local_64);
    }
    local_8 = 0xffffffff;
    FUN_007538f0();
  }
  uVar4 = (uint)*(byte *)(local_6c + 0x14);
  puVar2 = (undefined4 *)FID_conflict_end(local_a4);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_a8);
  FUN_00756790(*puVar2,uVar1,uVar4);
  FUN_0078a770();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

