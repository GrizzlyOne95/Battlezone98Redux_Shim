
void FUN_006e70d0(void)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  error_condition *in_stack_0000001c;
  undefined1 local_24 [8];
  error_condition local_1c [12];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851338;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006de390(5);
  bVar1 = std::error_condition::operator==(in_stack_0000001c,local_1c);
  if (bVar1) {
    FUN_006d08b0(0x400,"asio handle_proxy_write timer cancelled");
    local_8 = 0xffffffff;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  else {
    cVar2 = FUN_006ab7d0(uVar3);
    if (cVar2 == '\0') {
      FUN_006d08b0(0x400,"asio handle_proxy_write timer expired");
      FUN_006d7640();
      uVar4 = make_error_code(local_24,9);
      FUN_006cadd0(uVar4);
    }
    else {
      FUN_006f1700(1,"asio handle_proxy_write",in_stack_0000001c);
      FUN_006cadd0(in_stack_0000001c);
    }
    local_8 = 0xffffffff;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  ExceptionList = local_10;
  return;
}

