
void __fastcall FUN_0078ee10(int param_1)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_2c [16];
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined4 local_c;
  int local_8;
  
  local_10 = abStack_2c;
  local_8 = param_1;
  local_14 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_2c,
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(param_1 + 0x144));
  uStack_18 = FUN_00489390();
  uStack_1c = 0x78ee4f;
  local_c = uStack_18;
  FUN_007c7930();
  return;
}

