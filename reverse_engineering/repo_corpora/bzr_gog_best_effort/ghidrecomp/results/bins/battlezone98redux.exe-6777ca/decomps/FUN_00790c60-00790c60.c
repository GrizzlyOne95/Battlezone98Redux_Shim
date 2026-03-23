
void FUN_00790c60(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_44 [20];
  undefined4 uStack_30;
  uint uStack_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  uint local_18;
  char *local_14;
  int local_10;
  char *local_c;
  char local_5;
  
  DAT_00918314 = 1;
  uStack_2c = 0x790c81;
  local_18 = FUN_007cb0a0();
  if (local_18 != 0xffffffff) {
    DAT_0091831c = local_18;
  }
  uStack_2c = DAT_0091831c & 0xff;
  local_20 = abStack_44;
  local_24 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_44,
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_10 + 0x150));
  local_1c = FUN_004880e0();
  uStack_2c = 0x790cc7;
  local_14 = (char *)FUN_0041f870();
  local_c = &DAT_00915540;
  local_28 = &DAT_00915540;
  do {
    local_5 = *local_14;
    *local_c = local_5;
    local_14 = local_14 + 1;
    local_c = local_c + 1;
  } while (local_5 != '\0');
  uStack_2c = 5;
  uStack_30 = 0x790d06;
  FUN_00434170();
  DAT_00918328 = 0;
  uStack_2c = 0;
  uStack_30 = 0x790d23;
  FUN_007c9170();
  uStack_2c = 0x790d28;
  FUN_0078bb00();
  uStack_2c = 0x17;
  uStack_30 = 0x790d38;
  FUN_007c7930();
  return;
}

