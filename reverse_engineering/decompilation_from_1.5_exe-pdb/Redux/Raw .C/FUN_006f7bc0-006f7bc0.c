
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_006f7bc0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            undefined4 param_2,undefined4 param_3)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845ab8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pbVar1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00417780(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,pbVar1);
  local_8 = 0;
  uVar2 = FUN_00417780(param_3);
  FUN_006ffa70(uVar2);
  ExceptionList = local_10;
  return param_1;
}

