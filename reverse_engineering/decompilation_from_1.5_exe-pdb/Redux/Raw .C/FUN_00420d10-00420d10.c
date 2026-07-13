
/* WARNING: Removing unreachable block (ram,0x00420dce) */
/* WARNING: Removing unreachable block (ram,0x00420e9d) */

fpos<int> * __thiscall
FUN_00420d10(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,fpos<int> *param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  __int64 _Var5;
  uint in_stack_00000020;
  
  _Var5 = FUN_00421b00();
  iVar1 = (int)_Var5;
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  if ((pcVar2 != (char *)0x0) &&
     (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
     *(char **)(param_1 + 0x38) < pcVar2)) {
    pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
    *(char **)(param_1 + 0x38) = pcVar2;
  }
  if ((iVar1 != *(int *)_BADOFF_exref) ||
     ((int)((ulonglong)_Var5 >> 0x20) != *(int *)(_BADOFF_exref + 4))) {
    if (((in_stack_00000020 & 1) == 0) ||
       (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1),
       pcVar2 == (char *)0x0)) {
      if (((in_stack_00000020 & 2) == 0) ||
         (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
         pcVar2 == (char *)0x0)) {
        _Var5 = *(__int64 *)_BADOFF_exref;
      }
      else if ((_Var5 < 0) ||
              (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1),
              *(int *)(param_1 + 0x38) - (int)pcVar2 < _Var5)) {
        _Var5 = *(__int64 *)_BADOFF_exref;
      }
      else {
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
        std::basic_streambuf<char,struct_std::char_traits<char>_>::pbump
                  (param_1,(int)(pcVar2 + (iVar1 - (int)pcVar3)));
      }
    }
    else if ((_Var5 < 0) ||
            (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1),
            *(int *)(param_1 + 0x38) - (int)pcVar2 < _Var5)) {
      _Var5 = *(__int64 *)_BADOFF_exref;
    }
    else {
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
      std::basic_streambuf<char,struct_std::char_traits<char>_>::gbump
                (param_1,(int)(pcVar2 + (iVar1 - (int)pcVar3)));
      if (((in_stack_00000020 & 2) != 0) &&
         (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
         pcVar2 != (char *)0x0)) {
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(param_1);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
        pcVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(param_1);
        std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                  (param_1,pcVar4,pcVar3,pcVar2);
      }
    }
  }
  std::fpos<int>::fpos<int>(param_2,_Var5);
  return param_2;
}

