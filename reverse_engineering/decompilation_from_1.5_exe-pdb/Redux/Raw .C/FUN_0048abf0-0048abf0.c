
void __fastcall FUN_0048abf0(int *param_1)

{
  char cVar1;
  int in_stack_fffffff0;
  int local_c;
  int *local_8;
  
  local_8 = param_1;
  if (*param_1 != 0) {
    local_c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sbumpc
                        ((basic_streambuf<char,struct_std::char_traits<char>_> *)*param_1);
    eof(in_stack_fffffff0);
    cVar1 = eq_int_type(&stack0xfffffff0,&local_c);
    if (cVar1 == '\0') {
      *(undefined1 *)(local_8 + 1) = 0;
      return;
    }
  }
  *local_8 = 0;
  *(undefined1 *)(local_8 + 1) = 1;
  return;
}

