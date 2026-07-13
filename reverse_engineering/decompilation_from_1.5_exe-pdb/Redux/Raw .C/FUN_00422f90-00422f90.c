
basic_streambuf<char,struct_std::char_traits<char>_> * __thiscall
FUN_00422f90(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2,
            undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008452e9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::basic_streambuf<char,struct_std::char_traits<char>_>::
  basic_streambuf<char,struct_std::char_traits<char>_>(param_1);
  local_8 = 0;
  *(undefined ***)param_1 =
       std::basic_stringbuf<char,struct_std::char_traits<char>,class_std::allocator<char>_>::vftable
  ;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x40));
  uVar2 = FUN_00424460(param_3);
  uVar3 = FUN_004170c0(uVar2,uVar1);
  uVar4 = FUN_0041f870(uVar3);
  FUN_00424350(uVar4,uVar3,uVar2);
  ExceptionList = local_10;
  return param_1;
}

