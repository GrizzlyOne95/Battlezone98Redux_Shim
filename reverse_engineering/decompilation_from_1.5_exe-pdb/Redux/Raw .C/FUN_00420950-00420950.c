
void __fastcall FUN_00420950(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  int unaff_ESI;
  
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (pcVar1 == (char *)0x0) {
    eof(unaff_ESI);
    return;
  }
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(param_1);
  if (pcVar2 <= pcVar1) {
    if (((*(uint *)(param_1 + 0x3c) & 4) == 0) &&
       (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
       pcVar1 != (char *)0x0)) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
      if ((pcVar2 < pcVar1) ||
         (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1),
         pcVar1 < *(char **)(param_1 + 0x38))) {
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
        if (*(char **)(param_1 + 0x38) < pcVar1) {
          pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
          *(char **)(param_1 + 0x38) = pcVar1;
        }
        pcVar1 = *(char **)(param_1 + 0x38);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                  (param_1,pcVar3,pcVar2,pcVar1);
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
        FUN_00417ab0(pcVar1);
        return;
      }
    }
    eof(unaff_ESI);
    return;
  }
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  FUN_00417ab0(pcVar1);
  return;
}

