
undefined1 * __thiscall FUN_006d4cd0(undefined1 *param_1,char param_2)

{
  char cVar1;
  int in_stack_fffffff0;
  int local_c;
  undefined1 *local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 4) != 0) {
    local_c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                        (*(basic_streambuf<char,struct_std::char_traits<char>_> **)(param_1 + 4),
                         param_2);
    eof(in_stack_fffffff0);
    cVar1 = eq_int_type(&stack0xfffffff0,&local_c);
    if (cVar1 == '\0') {
      return local_8;
    }
  }
  *local_8 = 1;
  return local_8;
}

