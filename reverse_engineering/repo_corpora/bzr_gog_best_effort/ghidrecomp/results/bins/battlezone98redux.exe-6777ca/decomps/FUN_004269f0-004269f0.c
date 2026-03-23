
bool FUN_004269f0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2)

{
  int iVar1;
  
  iVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::compare
                    (param_1,param_2);
  return iVar1 < 0;
}

