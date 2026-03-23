
void FUN_006d6190(void)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  error_condition *in_stack_0000002c;
  undefined1 local_2c [8];
  error_condition local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008534d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 2;
  FUN_006ab750(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    puVar3 = (undefined4 *)make_error_code(local_2c,9);
    local_1c = *puVar3;
    local_18 = puVar3[1];
  }
  else {
    FUN_006de390(5);
    bVar2 = std::error_condition::operator==(in_stack_0000002c,local_24);
    if (bVar2) {
      FUN_006d08b0(0x400,"asio handle_connect_timeout timer cancelled");
      local_8._0_1_ = 1;
      FUN_006ca8c0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x00000014);
      ExceptionList = local_10;
      return;
    }
    FUN_006de3e0(1,"asio handle_connect_timeout",in_stack_0000002c);
    local_1c = *(undefined4 *)in_stack_0000002c;
    local_18 = *(undefined4 *)(in_stack_0000002c + 4);
  }
  FUN_006d08b0(0x400,"TCP connect timed out");
  FUN_00421ec0();
  FUN_006d7640();
  FUN_006cadd0(&local_1c);
  local_8._0_1_ = 1;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000014);
  ExceptionList = local_10;
  return;
}

