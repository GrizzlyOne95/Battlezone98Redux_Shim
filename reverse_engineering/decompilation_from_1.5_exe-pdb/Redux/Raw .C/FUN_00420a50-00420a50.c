
fpos<int> * __thiscall
FUN_00420a50(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,fpos<int> *param_2,
            uint param_3,int param_4,int param_5,uint param_6)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  if ((pcVar1 != (char *)0x0) &&
     (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
     *(char **)(param_1 + 0x38) < pcVar1)) {
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
    *(char **)(param_1 + 0x38) = pcVar1;
  }
  if (((param_6 & 1) == 0) ||
     (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1),
     pcVar1 == (char *)0x0)) {
    if (((param_6 & 2) == 0) ||
       (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
       pcVar1 == (char *)0x0)) {
      if (param_3 != 0 || param_4 != 0) {
        param_3 = *(uint *)_BADOFF_exref;
        param_4 = *(int *)(_BADOFF_exref + 4);
      }
    }
    else {
      if (param_5 == 2) {
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        uVar4 = *(int *)(param_1 + 0x38) - (int)pcVar1;
        bVar6 = CARRY4(uVar4,param_3);
        param_3 = uVar4 + param_3;
        param_4 = ((int)uVar4 >> 0x1f) + param_4 + (uint)bVar6;
      }
      else if (param_5 == 1) {
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        uVar4 = (int)pcVar1 - (int)pcVar2;
        bVar6 = CARRY4(uVar4,param_3);
        param_3 = uVar4 + param_3;
        param_4 = ((int)uVar4 >> 0x1f) + param_4 + (uint)bVar6;
      }
      else if (param_5 != 0) {
        param_3 = *(uint *)_BADOFF_exref;
        param_4 = *(int *)(_BADOFF_exref + 4);
      }
      if (-1 < param_4) {
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        iVar5 = *(int *)(param_1 + 0x38) - (int)pcVar1 >> 0x1f;
        if ((param_4 <= iVar5) &&
           ((param_4 < iVar5 || (param_3 <= (uint)(*(int *)(param_1 + 0x38) - (int)pcVar1))))) {
          pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
          pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
          std::basic_streambuf<char,struct_std::char_traits<char>_>::pbump
                    (param_1,(int)(pcVar1 + (param_3 - (int)pcVar2)));
          goto LAB_00420cee;
        }
      }
      param_3 = *(uint *)_BADOFF_exref;
      param_4 = *(int *)(_BADOFF_exref + 4);
    }
  }
  else {
    if (param_5 == 2) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      uVar4 = *(int *)(param_1 + 0x38) - (int)pcVar1;
      bVar6 = CARRY4(uVar4,param_3);
      param_3 = uVar4 + param_3;
      param_4 = ((int)uVar4 >> 0x1f) + param_4 + (uint)bVar6;
    }
    else if ((param_5 == 1) && ((param_6 & 2) == 0)) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      uVar4 = (int)pcVar1 - (int)pcVar2;
      bVar6 = CARRY4(uVar4,param_3);
      param_3 = uVar4 + param_3;
      param_4 = ((int)uVar4 >> 0x1f) + param_4 + (uint)bVar6;
    }
    else if (param_5 != 0) {
      param_3 = *(uint *)_BADOFF_exref;
      param_4 = *(int *)(_BADOFF_exref + 4);
    }
    if (-1 < param_4) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      iVar5 = *(int *)(param_1 + 0x38) - (int)pcVar1 >> 0x1f;
      if ((param_4 <= iVar5) &&
         ((param_4 < iVar5 || (param_3 <= (uint)(*(int *)(param_1 + 0x38) - (int)pcVar1))))) {
        pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
        pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
        std::basic_streambuf<char,struct_std::char_traits<char>_>::gbump
                  (param_1,(int)(pcVar1 + (param_3 - (int)pcVar2)));
        if (((param_6 & 2) != 0) &&
           (pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1),
           pcVar1 != (char *)0x0)) {
          pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::epptr(param_1);
          pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
          pcVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(param_1);
          std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                    (param_1,pcVar3,pcVar2,pcVar1);
        }
        goto LAB_00420cee;
      }
    }
    param_3 = *(uint *)_BADOFF_exref;
    param_4 = *(int *)(_BADOFF_exref + 4);
  }
LAB_00420cee:
  std::fpos<int>::fpos<int>(param_2,CONCAT44(param_4,param_3));
  return param_2;
}

