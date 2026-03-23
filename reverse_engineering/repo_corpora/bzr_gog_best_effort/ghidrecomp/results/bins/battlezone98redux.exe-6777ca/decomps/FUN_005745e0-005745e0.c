
void __fastcall FUN_005745e0(basic_streambuf<char,struct_std::char_traits<char>_> *param_1)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *local_5c;
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(param_1 + 0x3c) & 2) == 0) {
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
    if (pcVar1 != (char *)0x0) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
      if (*(char **)(param_1 + 0x38) < pcVar1) {
        local_5c = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
      }
      else {
        local_5c = *(char **)(param_1 + 0x38);
      }
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(param_1);
      iVar3 = (int)local_5c - (int)pcVar1;
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pbase(param_1);
      basic_string<>(pcVar1,iVar3);
      basic_string<>(local_50);
      ~basic_string<>();
      goto LAB_00574717;
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 4) == 0) {
    pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
    if (pcVar1 != (char *)0x0) {
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::egptr(param_1);
      pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      iVar3 = (int)pcVar1 - (int)pcVar2;
      pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::eback(param_1);
      basic_string<>(pcVar1,iVar3);
      basic_string<>(local_38);
      ~basic_string<>();
      goto LAB_00574717;
    }
  }
  basic_string<>();
  basic_string<>(local_20);
  ~basic_string<>();
LAB_00574717:
  FUN_0083e885();
  return;
}

