
undefined4 __fastcall FUN_00421480(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  int unaff_ESI;
  int local_10;
  undefined4 local_c;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_8;
  
  local_8 = param_1;
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_8);
    pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(local_8);
    if (pcVar2 < pcVar3) {
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_8);
      uVar4 = FUN_00417ab0(pcVar2);
      return uVar4;
    }
  }
  local_c = (**(code **)(*(int *)local_8 + 0x1c))();
  local_10 = eof(unaff_ESI);
  cVar1 = eq_int_type(&local_10,&local_c);
  if (cVar1 == '\0') {
    (**(code **)(*(int *)local_8 + 0x10))(local_c);
  }
  return local_c;
}

