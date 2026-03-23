
void FUN_006e8de0(void)

{
  char cVar1;
  bool bVar2;
  error_condition *in_stack_0000001c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_8c [8];
  undefined4 uStack_84;
  undefined1 *puStack_80;
  char *pcStack_7c;
  error_condition local_64 [8];
  undefined1 *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00854888;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    cVar1 = FUN_006caba0();
    if (cVar1 != '\0') {
      local_5c = abStack_8c;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_8c,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &stack0x00000004);
      shared_ptr<>(local_48 + 0x918);
      FUN_006f2840();
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    pcStack_7c = (char *)0x6e8e2f;
    FUN_006de390();
    pcStack_7c = (char *)0x6e8e3b;
    bVar2 = std::error_condition::operator==(in_stack_0000001c,local_64);
    if (bVar2) {
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      pcStack_7c = (char *)0x6e8e62;
      local_58 = FUN_006ab780();
      local_8._0_1_ = 1;
      pcStack_7c = "pong_timeout error: ";
      puStack_80 = local_44;
      uStack_84 = 0x6e8e81;
      local_50 = local_58;
      local_54 = FUN_006dd7f0();
      local_8._0_1_ = 2;
      pcStack_7c = (char *)0x1;
      puStack_80 = (undefined1 *)0x6e8ea5;
      local_4c = local_54;
      FUN_006d46a0();
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

