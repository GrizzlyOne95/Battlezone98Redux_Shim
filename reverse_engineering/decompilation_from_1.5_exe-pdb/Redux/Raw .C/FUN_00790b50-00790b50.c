
void FUN_00790b50(void)

{
  int iVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_60 [16];
  undefined4 uStack_50;
  undefined4 *puStack_4c;
  uint uStack_48;
  undefined1 local_44 [12];
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085edc8;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_4c = (undefined4 *)0x790b86;
  iVar1 = FUN_007c7a20();
  if (iVar1 == 1) {
    puStack_4c = (undefined4 *)0x790b97;
    vector<>();
    local_8 = 0;
    local_18 = 1;
    puStack_4c = &local_18;
    uStack_50 = 0x790bb1;
    FUN_0041ff90();
    local_2c = abStack_60;
    local_30 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_60,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(local_14 + 0x150));
    local_20 = FUN_00489230();
    puStack_4c = &local_20;
    uStack_50 = 0x790be8;
    local_1c = local_20;
    FUN_0041ff90();
    local_34 = abStack_60;
    local_38 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_60,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(local_14 + 0x150));
    local_28 = FUN_00489390();
    puStack_4c = &local_28;
    uStack_50 = 0x790c1f;
    local_24 = local_28;
    FUN_0041ff90();
    puStack_4c = (undefined4 *)local_44;
    uStack_50 = 0x790c31;
    FUN_007c7aa0();
    local_8 = 0xffffffff;
    puStack_4c = (undefined4 *)0x790c40;
    FUN_0041fe20();
  }
  puStack_4c = (undefined4 *)0x790c4e;
  FUN_007c79a0();
  ExceptionList = local_10;
  return;
}

