
void __thiscall FUN_007d71d0(uint *param_1,uint param_2)

{
  uint local_c;
  
  FUN_007d7220();
  if (param_2 == 0xffffffff) {
    local_c = 0;
  }
  else {
    local_c = param_2;
  }
  *param_1 = local_c;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1),*param_1);
  return;
}

