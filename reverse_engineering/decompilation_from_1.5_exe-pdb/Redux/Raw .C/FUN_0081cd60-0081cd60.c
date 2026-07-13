
void __thiscall
FUN_0081cd60(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            uint param_2,uint param_3,char *param_4)

{
  uint uVar1;
  
  uVar1 = FUN_00416290(param_4);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::replace
            (param_1,param_2,param_3,param_4,uVar1);
  return;
}

