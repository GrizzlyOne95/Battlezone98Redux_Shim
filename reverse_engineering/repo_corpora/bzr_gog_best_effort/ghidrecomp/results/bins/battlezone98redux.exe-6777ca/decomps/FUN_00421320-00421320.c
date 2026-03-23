
int __thiscall
FUN_00421320(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,int param_2)

{
  char cVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> bVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar6;
  int unaff_ESI;
  int local_18;
  undefined4 local_14;
  int local_10;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_c;
  undefined1 local_5;
  
  local_c = param_1;
  pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (pcVar3 != (char *)0x0) {
    pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(local_c);
    pcVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
    if (pcVar3 < pcVar4) {
      local_10 = eof(unaff_ESI);
      cVar1 = eq_int_type(&local_10,&param_2);
      if (cVar1 == '\0') {
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
        local_14 = FUN_00417ab0(pcVar3 + -1);
        cVar1 = eq_int_type(&local_14,&param_2);
        if (cVar1 == '\0') goto LAB_004213c7;
      }
      std::basic_streambuf<char,struct_std::char_traits<char>_>::_Gndec(local_c);
      iVar5 = not_eof(&param_2);
      return iVar5;
    }
  }
LAB_004213c7:
  if (*(int *)(local_c + 0x50) != 0) {
    local_18 = eof(unaff_ESI);
    cVar1 = eq_int_type(&local_18,&param_2);
    if (cVar1 == '\0') {
      if (*(int *)(local_c + 0x40) == 0) {
        local_5 = FUN_00417aa0(&param_2);
        cVar1 = FUN_00417ed0(&local_5,*(undefined4 *)(local_c + 0x50));
        if (cVar1 != '\0') {
          return param_2;
        }
      }
      pbVar6 = (basic_streambuf<char,struct_std::char_traits<char>_> *)
               std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_c);
      if (pbVar6 != local_c + 0x44) {
        bVar2 = (basic_streambuf<char,struct_std::char_traits<char>_>)FUN_00417aa0(&param_2);
        local_c[0x44] = bVar2;
        FUN_004235c0();
        return param_2;
      }
      iVar5 = eof(unaff_ESI);
      return iVar5;
    }
  }
  iVar5 = eof(unaff_ESI);
  return iVar5;
}

