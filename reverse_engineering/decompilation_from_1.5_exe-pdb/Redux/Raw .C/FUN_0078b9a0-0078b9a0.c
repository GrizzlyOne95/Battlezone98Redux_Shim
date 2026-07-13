
void FUN_0078b9a0(void)

{
  char cVar1;
  int iVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined4 uStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  uint uStack_48;
  uint uStack_44;
  undefined1 *local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  int local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uStack_44;
  if (((DAT_0094550c != 0) && (-1 < (int)DAT_0091831c)) && (DAT_00918133 == '\0')) {
    uStack_48 = 0x78b9f9;
    basic_string<>();
    local_8 = 0;
    uStack_48 = 0x78ba05;
    iVar2 = FUN_00572a70();
    if ((iVar2 == 0) && (DAT_00918314 == 0)) {
      uStack_48 = DAT_0091831c & 0xff;
      uStack_4c = 0x78ba1f;
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00482850();
      local_40 = (undefined1 *)&uStack_60;
      local_3c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&uStack_60,pbVar3);
      local_38 = FUN_004880e0();
      uStack_48 = local_38 + 0x48;
      uStack_4c = 0x78ba4a;
      FID_conflict_operator_();
    }
    uStack_48 = 0x78ba52;
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      uStack_48 = 0x78ba61;
      uStack_48 = FUN_0041f870();
      uStack_4c = 0x78ba67;
      local_30 = FUN_00481af0();
      if (local_30 != 0) {
        uStack_48 = 0x78ba7b;
        uStack_48 = FUN_0041f870();
        uStack_4c = 0x78ba81;
        local_34 = FUN_00481a60();
        uStack_48 = 0xffffffff;
        uStack_4c = 0;
        uStack_50 = 100;
        uStack_54 = 0x78ba95;
        uStack_54 = FUN_0041f870();
        uStack_58 = local_34;
        iStack_5c = local_30;
        uStack_60 = 0x78baa3;
        FUN_0043aac0();
        uStack_48 = 0;
        uStack_4c = 0x78baad;
        FUN_0043a170();
        uStack_48 = 0x78bab8;
        uStack_48 = FUN_0041f870();
        uStack_4c = 0x78babe;
        FUN_00481990();
        DAT_00918318 = local_30;
      }
    }
    local_8 = 0xffffffff;
    uStack_48 = 0x78bad8;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  uStack_44 = 0x78baed;
  FUN_0083e885();
  return;
}

