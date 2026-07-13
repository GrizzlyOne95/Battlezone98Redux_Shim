
undefined4
FUN_00426a20(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  pbVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                     (param_2,param_3);
  uVar2 = FUN_00417780(pbVar1,uVar2);
  basic_string<>(uVar2);
  return param_1;
}

