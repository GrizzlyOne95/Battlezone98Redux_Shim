
void __thiscall
FUN_00705640(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            int param_3)

{
  uint uVar1;
  char *pcVar2;
  char **_EndPtr;
  int _Radix;
  undefined4 local_40;
  ulong local_3c;
  undefined1 local_38 [4];
  uint local_34;
  uint local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856e98;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  basic_string<>(local_14,param_1);
  local_8 = 0;
  local_30 = 0;
  while( true ) {
    uVar1 = FUN_004170c0();
    if (uVar1 <= local_30) break;
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](param_2,local_30);
    if (*pcVar2 == ' ') {
      local_34 = local_34 + 1;
    }
    else {
      pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               operator[](param_2,local_30);
      if ('/' < *pcVar2) {
        pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](param_2,local_30);
        if (*pcVar2 < ':') {
          pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::operator[](param_2,local_30);
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator+=(local_2c,*pcVar2);
        }
      }
    }
    local_30 = local_30 + 1;
  }
  _Radix = 10;
  _EndPtr = (char **)0x0;
  pcVar2 = (char *)FUN_0041f870();
  local_3c = strtoul(pcVar2,_EndPtr,_Radix);
  if ((local_34 == 0) || (local_3c == 0)) {
    local_40 = 0;
    FUN_0070f870(param_3,param_3 + 4,&local_40);
  }
  else {
    local_3c = htonl(local_3c / local_34);
    FUN_006da2a0(&local_3c,local_38,param_3);
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

