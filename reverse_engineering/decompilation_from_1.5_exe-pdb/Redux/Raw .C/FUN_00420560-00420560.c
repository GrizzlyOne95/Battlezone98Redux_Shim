
int __thiscall
FUN_00420560(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int unaff_ESI;
  int local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  char *local_18;
  uint local_14;
  uint local_10;
  char *local_c;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_8;
  
  local_8 = param_1;
  if ((*(uint *)(param_1 + 0x3c) & 2) == 0) {
    local_28 = eof(unaff_ESI);
    cVar1 = eq_int_type(&local_28,&param_2);
    if (cVar1 == '\0') {
      if ((((*(uint *)(local_8 + 0x3c) & 8) != 0) &&
          (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8),
          pcVar2 != (char *)0x0)) &&
         (pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8),
         pcVar2 < *(char **)(local_8 + 0x38))) {
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(local_8);
        pcVar2 = *(char **)(local_8 + 0x38);
        pcVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(local_8);
        std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                  (local_8,pcVar4,pcVar2,pcVar3);
      }
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8);
      if (pcVar2 != (char *)0x0) {
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(local_8);
        if (pcVar2 < pcVar3) {
          cVar1 = FUN_00417aa0(&param_2);
          pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::_Pninc(local_8);
          *pcVar2 = cVar1;
          return param_2;
        }
      }
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8);
      if (pcVar2 == (char *)0x0) {
        local_20 = 0;
      }
      else {
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(local_8);
        pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(local_8);
        local_20 = (int)pcVar2 - (int)pcVar3;
      }
      local_1c = local_20;
      local_10 = local_20;
      if (local_20 >> 1 < 0x20) {
        local_24 = 0x20;
      }
      else {
        local_24 = local_20 >> 1;
      }
      for (local_14 = local_24; (local_14 != 0 && (0x7fffffff - local_14 < local_20));
          local_14 = local_14 >> 1) {
      }
      if (local_14 == 0) {
        param_2 = eof(unaff_ESI);
      }
      else {
        local_10 = local_20 + local_14;
        local_c = (char *)allocate(local_10);
        local_18 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(local_8);
        if (local_1c != 0) {
          std::char_traits<char>::copy(local_c,local_18,local_1c);
        }
        if (local_1c == 0) {
          *(char **)(local_8 + 0x38) = local_c;
          std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                    (local_8,local_c,local_c + local_10);
          if ((*(uint *)(local_8 + 0x3c) & 4) == 0) {
            std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                      (local_8,local_c,local_c,local_c + 1);
          }
          else {
            std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                      (local_8,local_c,(char *)0x0,local_c);
          }
        }
        else {
          *(char **)(local_8 + 0x38) = local_c + (*(int *)(local_8 + 0x38) - (int)local_18);
          pcVar4 = local_c + local_10;
          pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8);
          pcVar2 = local_c + ((int)pcVar2 - (int)local_18);
          pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(local_8);
          std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                    (local_8,local_c + ((int)pcVar3 - (int)local_18),pcVar2,pcVar4);
          if ((*(uint *)(local_8 + 0x3c) & 4) == 0) {
            pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(local_8);
            pcVar2 = pcVar2 + 1;
            pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(local_8);
            std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                      (local_8,local_c,local_c + ((int)pcVar3 - (int)local_18),pcVar2);
          }
          else {
            std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                      (local_8,local_c,(char *)0x0,local_c);
          }
        }
        if ((*(uint *)(local_8 + 0x3c) & 1) != 0) {
          FUN_00417180(local_18,local_1c);
        }
        *(uint *)(local_8 + 0x3c) = *(uint *)(local_8 + 0x3c) | 1;
        cVar1 = FUN_00417aa0(&param_2);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::_Pninc(local_8);
        *pcVar2 = cVar1;
      }
    }
    else {
      param_2 = not_eof(&param_2);
    }
  }
  else {
    param_2 = eof(unaff_ESI);
  }
  return param_2;
}

