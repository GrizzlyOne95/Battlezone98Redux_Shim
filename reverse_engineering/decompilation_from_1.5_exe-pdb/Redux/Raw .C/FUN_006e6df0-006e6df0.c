
void FUN_006e6df0(void)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  error_condition *in_stack_00000024;
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  error_condition local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00854620;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_006ab750(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    FUN_006bb810(local_2c);
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      puVar3 = (undefined4 *)make_error_code(local_3c,9);
      local_1c = *puVar3;
      local_18 = puVar3[1];
    }
    else {
      puVar3 = (undefined4 *)FUN_006bb810(local_34);
      local_1c = *puVar3;
      local_18 = puVar3[1];
    }
  }
  else {
    FUN_006de390(5);
    bVar2 = std::error_condition::operator==(in_stack_00000024,local_24);
    if (bVar2) {
      FUN_006d08b0(0x400,"asio post init timer cancelled");
      local_8 = local_8 & 0xffffff00;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x0000000c);
      ExceptionList = local_10;
      return;
    }
    FUN_006f1700(1,"asio handle_post_init_timeout",in_stack_00000024);
    local_1c = *(undefined4 *)in_stack_00000024;
    local_18 = *(undefined4 *)(in_stack_00000024 + 4);
  }
  FUN_006d08b0(0x400,"Asio transport post-init timed out");
  FUN_006d7640();
  FUN_006cadd0(&local_1c);
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x0000000c);
  ExceptionList = local_10;
  return;
}

