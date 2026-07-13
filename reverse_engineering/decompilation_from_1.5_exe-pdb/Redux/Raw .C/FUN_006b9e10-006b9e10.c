
uint __thiscall FUN_006b9e10(int param_1,char *param_2,uint param_3)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x60) == 0) {
    *(undefined4 *)(param_1 + 0x70) = 3;
    local_c = 0;
  }
  else {
    if (param_3 < *(uint *)(param_1 + 0x60)) {
      local_c = param_3;
    }
    else {
      local_c = *(uint *)(param_1 + 0x60);
      *(undefined4 *)(param_1 + 0x70) = 3;
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_1 + 0x24),param_2,local_c);
    *(uint *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) - local_c;
  }
  return local_c;
}

