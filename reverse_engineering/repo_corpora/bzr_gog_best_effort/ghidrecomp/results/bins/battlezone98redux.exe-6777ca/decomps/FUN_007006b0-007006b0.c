
int __thiscall
FUN_007006b0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,uint param_5)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008564c1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  shared_ptr<>(&param_2);
  local_8._0_1_ = 1;
  basic_string<>(uVar1);
  local_8._0_1_ = 2;
  basic_string<>();
  local_8._0_1_ = 3;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,4);
  *(undefined4 *)(param_1 + 0x50) = param_4;
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 1;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x38),param_5);
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

