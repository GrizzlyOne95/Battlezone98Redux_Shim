
void __fastcall FUN_00420860(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int unaff_ESI;
  int local_14;
  int local_10;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_c;
  undefined1 local_5;
  
  local_c = param_1;
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
    pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(local_c);
    if (pcVar3 < pcVar2) {
      local_10 = eof(unaff_ESI);
      cVar1 = eq_int_type(&local_10,&stack0x00000004);
      if (cVar1 == '\0') {
        local_5 = FUN_00417aa0(&stack0x00000004);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
        cVar1 = eq(&local_5,pcVar2 + -1);
        if ((cVar1 == '\0') && ((*(uint *)(local_c + 0x3c) & 2) != 0)) goto LAB_004208f0;
      }
      std::basic_streambuf<char,struct_std::char_traits<char>_>::gbump(local_c,-1);
      local_14 = eof(unaff_ESI);
      cVar1 = eq_int_type(&local_14,&stack0x00000004);
      if (cVar1 == '\0') {
        cVar1 = FUN_00417aa0(&stack0x00000004);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
        *pcVar2 = cVar1;
      }
      not_eof(&stack0x00000004);
      return;
    }
  }
LAB_004208f0:
  eof(unaff_ESI);
  return;
}

