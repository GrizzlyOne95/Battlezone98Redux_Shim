
void FUN_006bac90(undefined4 param_1,byte *param_2,int param_3)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  byte abStack_3c [4];
  uint local_38;
  uint local_34;
  byte abStack_30 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848fd8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14);
  local_8 = 0;
  local_34 = 0;
  local_38 = 0;
  while (iVar3 = param_3 + -1, param_3 != 0) {
    abStack_30[local_34] = *param_2;
    local_34 = local_34 + 1;
    param_2 = param_2 + 1;
    param_3 = iVar3;
    if (local_34 == 3) {
      abStack_3c[0] = (byte)((int)(abStack_30[0] & 0xfc) >> 2);
      abStack_3c[1] = (abStack_30[0] & 3) * '\x10' + (char)((int)(abStack_30[1] & 0xf0) >> 4);
      abStack_3c[2] = (char)((int)(abStack_30[2] & 0xc0) >> 6) + (abStack_30[1] & 0xf) * '\x04';
      abStack_3c[3] = abStack_30[2] & 0x3f;
      for (local_34 = 0; (int)local_34 < 4; local_34 = local_34 + 1) {
        pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[]((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&DAT_0260b070,(uint)abStack_3c[local_34]);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        operator+=(local_2c,*pcVar2);
      }
      local_34 = 0;
    }
  }
  if (local_34 != 0) {
    for (local_38 = local_34; uVar4 = local_38, (int)local_38 < 3; local_38 = local_38 + 1) {
      if (2 < local_38) {
        ___report_rangecheckfailure();
      }
      abStack_30[uVar4] = 0;
    }
    abStack_3c[0] = (byte)((int)(abStack_30[0] & 0xfc) >> 2);
    abStack_3c[1] = (abStack_30[0] & 3) * '\x10' + (char)((int)(abStack_30[1] & 0xf0) >> 4);
    abStack_3c[2] = (char)((int)(abStack_30[2] & 0xc0) >> 6) + (abStack_30[1] & 0xf) * '\x04';
    abStack_3c[3] = abStack_30[2] & 0x3f;
    for (local_38 = 0; (int)local_38 < (int)(local_34 + 1); local_38 = local_38 + 1) {
      pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               operator[]((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)&DAT_0260b070,(uint)abStack_3c[local_38]);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
                (local_2c,*pcVar2);
    }
    while (uVar4 = local_34 + 1, bVar1 = (int)local_34 < 3, local_34 = uVar4, bVar1) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
                (local_2c,'=');
    }
  }
  basic_string<>(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

