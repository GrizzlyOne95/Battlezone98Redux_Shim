
void FUN_00795f50(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_34 [20];
  undefined4 uStack_20;
  uint uStack_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fec8;
  local_10 = ExceptionList;
  uStack_1c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  if (DAT_0094555c != 0) {
    local_14 = abStack_34;
    local_18 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_34,
                          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)&stack0x00000004);
    FUN_00796000();
  }
  local_8 = 0xffffffff;
  uStack_20 = 0x795fb3;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

