
undefined1 __fastcall FUN_0048ac50(int *param_1)

{
  char cVar1;
  undefined1 uVar2;
  int in_stack_fffffff0;
  int local_c;
  int *local_8;
  
  local_8 = param_1;
  if (*param_1 != 0) {
    local_c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sgetc
                        ((basic_streambuf<char,struct_std::char_traits<char>_> *)*param_1);
    eof(in_stack_fffffff0);
    cVar1 = eq_int_type(&stack0xfffffff0,&local_c);
    if (cVar1 == '\0') {
      uVar2 = FUN_00417aa0(&local_c);
      *(undefined1 *)((int)local_8 + 5) = uVar2;
      goto LAB_0048acab;
    }
  }
  *local_8 = 0;
LAB_0048acab:
  *(undefined1 *)(local_8 + 1) = 1;
  return *(undefined1 *)((int)local_8 + 5);
}

