
void __thiscall FUN_00705220(int param_1,char *param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = FUN_004170c0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x38),iVar1 + param_3);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x38),param_2,param_3);
  return;
}

