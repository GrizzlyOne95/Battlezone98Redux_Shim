
void FUN_004888b0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_74 [12];
  undefined4 uStack_68;
  undefined1 *puStack_64;
  undefined1 *puStack_60;
  uint uStack_5c;
  undefined4 local_58;
  undefined1 *local_54;
  undefined4 local_50;
  undefined1 *local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849008;
  local_10 = ExceptionList;
  uStack_5c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_60 = &DAT_00915540;
  puStack_64 = (undefined1 *)0x4888e5;
  local_14 = uStack_5c;
  basic_string<>();
  local_8 = 0;
  local_4c = abStack_74;
  local_58 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_74,param_1);
  local_3c = FUN_004885d0();
  local_30 = 0;
  local_38 = local_3c;
  do {
    if (local_3c <= (int)local_30) {
      local_40 = 0xffffffff;
      local_8 = 0xffffffff;
      puStack_60 = (undefined1 *)0x48899e;
      ~basic_string<>();
LAB_004889a1:
      ExceptionList = local_10;
      uStack_5c = 0x4889b6;
      FUN_0083e885();
      return;
    }
    puStack_60 = (undefined1 *)(local_30 & 0xff);
    local_54 = &stack0xffffff88;
    local_50 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)&stack0xffffff88,param_1);
    puStack_60 = (undefined1 *)FUN_004880e0();
    puStack_64 = local_2c;
    uStack_68 = 0x488962;
    local_48 = puStack_60;
    local_44 = puStack_60;
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') {
      local_34 = local_30;
      local_8 = 0xffffffff;
      puStack_60 = (undefined1 *)0x488981;
      ~basic_string<>();
      goto LAB_004889a1;
    }
    local_30 = local_30 + 1;
  } while( true );
}

