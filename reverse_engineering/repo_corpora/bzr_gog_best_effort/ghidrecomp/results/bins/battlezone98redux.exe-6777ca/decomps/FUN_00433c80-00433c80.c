
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_00433c80(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            undefined4 param_2)

{
  undefined4 uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  
  uVar1 = FUN_00417780(param_2);
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00433f60(uVar1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,pbVar2);
  *(undefined4 *)(param_1 + 0x18) = 0;
  return param_1;
}

