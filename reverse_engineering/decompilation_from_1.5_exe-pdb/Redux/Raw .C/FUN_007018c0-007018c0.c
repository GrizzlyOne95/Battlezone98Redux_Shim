
void __thiscall FUN_007018c0(int param_1,undefined4 param_2)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008567d0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>(&DAT_00897554);
  local_8 = 0;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006b7490(local_44);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  uVar1 = FUN_0045e1a0(&DAT_00896ce8,0xffffffff);
  uVar3 = FUN_0045e1a0(&DAT_00871538,0xffffffff);
  if ((uVar1 == 0xffffffff) || ((uVar3 != 0xffffffff && (uVar1 < uVar3)))) {
    uVar4 = FUN_006b81d0();
    FUN_0070ef30(param_2,param_1 + 4,local_2c,uVar4);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    uVar4 = FUN_0045e1d0(local_5c,uVar1 + 1,0xffffffff);
    local_8._0_1_ = 3;
    uVar5 = FUN_0045e1d0(local_74,0,uVar1);
    local_8._0_1_ = 4;
    uVar6 = FUN_006b81d0();
    FUN_0070f020(param_2,param_1 + 4,uVar5,uVar4,uVar6);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

