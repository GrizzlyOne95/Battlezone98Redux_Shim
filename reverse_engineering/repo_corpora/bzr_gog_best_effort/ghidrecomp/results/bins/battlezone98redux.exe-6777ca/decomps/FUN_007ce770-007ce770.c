
void FUN_007ce770(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined1 local_ac [12];
  undefined1 local_a0 [12];
  undefined4 local_94;
  undefined1 local_90 [4];
  undefined1 local_8c [4];
  undefined4 local_88;
  undefined1 local_84 [12];
  uint local_78;
  uint local_68;
  int local_64;
  uint local_60;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008627c3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_78 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  local_60 = 0;
  FUN_007cea00(local_84);
  local_8._0_1_ = 2;
  FUN_007cea30(local_a0);
  local_8 = CONCAT31(local_8._1_3_,3);
  for (local_68 = 0; local_68 < *(uint *)(local_64 + 0x2958); local_68 = local_68 + 1) {
    FUN_007cec80(local_ac,0);
    FUN_004bb3d0();
  }
  while ((cVar1 = FID_conflict_operator__(local_a0), cVar1 != '\0' &&
         ((int)local_60 < *(int *)(local_64 + 0x294c)))) {
    FUN_007cec60();
    local_94 = FUN_004170c0();
    local_88 = 1;
    local_60 = local_60 + 1;
    uVar2 = FUN_007703e0();
    FUN_006cae50(uVar2);
    FUN_007332d0();
  }
  for (; (int)local_60 < *(int *)(local_64 + 0x294c); local_60 = local_60 + 1) {
    basic_string<>(&DAT_008a1ad8);
    local_8._0_1_ = 4;
    FUN_006cf320(local_5c);
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
  }
  for (; (int)local_60 < *(int *)(local_64 + 0x294c); local_60 = local_60 + 1) {
    basic_string<>(&DAT_008a1ad8);
    local_8._0_1_ = 5;
    FUN_006cf320(local_44);
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
  }
  puVar3 = (undefined4 *)FID_conflict_end(local_90);
  uVar2 = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_begin(local_8c);
  FUN_007cf1a0(*puVar3,uVar2);
  local_60 = 0;
  while (uVar4 = FUN_0048a830(), local_60 < uVar4) {
    uVar2 = FUN_006cf480(local_60);
    FUN_00449810(uVar2);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"\n");
    local_60 = local_60 + 1;
  }
  basic_string<>(local_2c);
  local_78 = local_78 | 1;
  local_8._0_1_ = 2;
  FUN_004bb3d0();
  local_8._0_1_ = 1;
  FUN_004bb3d0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0048a040();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

