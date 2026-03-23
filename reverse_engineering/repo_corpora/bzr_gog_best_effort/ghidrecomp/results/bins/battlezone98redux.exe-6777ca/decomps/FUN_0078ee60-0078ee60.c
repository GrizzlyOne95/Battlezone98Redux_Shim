
void __fastcall FUN_0078ee60(int param_1)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_40 [20];
  undefined4 uStack_2c;
  uint uStack_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  int local_14;
  char *local_10;
  char *local_c;
  char local_5;
  
  DAT_00918314 = 0;
  uStack_28 = (uint)(byte)DAT_0091831c;
  local_1c = abStack_40;
  local_14 = param_1;
  local_20 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_40,
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(param_1 + 0x144));
  local_18 = FUN_004880e0();
  uStack_28 = 0x78eeaa;
  local_10 = (char *)FUN_0041f870();
  local_c = &DAT_00915540;
  local_24 = &DAT_00915540;
  do {
    local_5 = *local_10;
    *local_c = local_5;
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (local_5 != '\0');
  uStack_28 = 5;
  uStack_2c = 0x78eee9;
  FUN_00434170();
  DAT_00918328 = 0;
  uStack_28 = 0;
  uStack_2c = 0x78ef06;
  FUN_007c9170();
  uStack_28 = 0x78ef0b;
  FUN_0078bb00();
  uStack_28 = 0x17;
  uStack_2c = 0x78ef1b;
  FUN_007c7930();
  return;
}

