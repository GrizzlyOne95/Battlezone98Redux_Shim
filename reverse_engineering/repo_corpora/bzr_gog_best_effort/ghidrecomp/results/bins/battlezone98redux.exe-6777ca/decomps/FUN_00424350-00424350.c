
void __thiscall
FUN_00424350(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,char *param_2,
            uint param_3,undefined4 param_4)

{
  char *pcVar1;
  char *pcVar2;
  char *local_10;
  
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = param_4;
  if ((param_3 != 0) && ((*(uint *)(param_1 + 0x3c) & 6) != 6)) {
    pcVar1 = (char *)allocate(param_3);
    std::char_traits<char>::copy(pcVar1,param_2,param_3);
    *(char **)(param_1 + 0x38) = pcVar1 + param_3;
    if ((*(uint *)(param_1 + 0x3c) & 4) == 0) {
      std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                (param_1,pcVar1,pcVar1,pcVar1 + param_3);
    }
    if ((*(uint *)(param_1 + 0x3c) & 2) == 0) {
      local_10 = pcVar1;
      if ((*(uint *)(param_1 + 0x3c) & 0x18) != 0) {
        local_10 = pcVar1 + param_3;
      }
      std::basic_streambuf<char,struct_std::char_traits<char>_>::setp
                (param_1,pcVar1,local_10,pcVar1 + param_3);
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
      if (pcVar2 == (char *)0x0) {
        std::basic_streambuf<char,struct_std::char_traits<char>_>::setg
                  (param_1,pcVar1,(char *)0x0,pcVar1);
      }
    }
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 1;
  }
  return;
}

