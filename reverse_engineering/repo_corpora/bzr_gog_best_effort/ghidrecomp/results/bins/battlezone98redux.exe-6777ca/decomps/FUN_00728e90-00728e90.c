
void __thiscall
FUN_00728e90(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859469;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_2);
  local_8 = 0;
  FUN_006d0c90(uVar1);
  uVar2 = FUN_006d0d10();
  iVar3 = forward<>(0x18,uVar2);
  local_8._0_1_ = 1;
  if (iVar3 == 0) {
    local_34 = 0;
  }
  else {
    uVar2 = FUN_00417780(local_2c);
    local_34 = basic_string<>(uVar2);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0045ba10(*(undefined4 *)(param_1 + 4));
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,local_34);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

