
void FUN_00742560(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 local_94 [16];
  undefined1 local_84 [4];
  undefined4 local_80;
  undefined1 local_7c [4];
  int *local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b1a0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_80 = FUN_0056f900(local_14);
  cVar1 = FUN_00742cf0();
  if (cVar1 != '\0') {
    basic_string<>(&DAT_008a1ad8);
    local_8 = 0;
    FUN_0042d8c0(local_7c);
    FID_conflict_begin(local_84);
    while( true ) {
      cVar1 = FUN_00420f10(local_84);
      if (cVar1 == '\0') break;
      iVar2 = FUN_0042da60();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(iVar2 + 0x2c));
      local_8._0_1_ = 1;
      while( true ) {
        uVar3 = FUN_004170c0();
        if (0x1f < uVar3) break;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c," ");
      }
      FUN_00449810(local_2c);
      FUN_0042da80();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
    uVar4 = FUN_0041f870();
    basic_string<>(uVar4);
    local_8._0_1_ = 2;
    basic_string<>("userPack");
    local_8._0_1_ = 3;
    puVar6 = local_5c;
    puVar5 = local_74;
    uVar4 = FUN_0073bcf0(local_94);
    (**(code **)(*local_78 + 0x20))(uVar4,puVar5,puVar6);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

