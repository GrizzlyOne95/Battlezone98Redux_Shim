
void FUN_006f5e70(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 in_stack_0000001c;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851338;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006e73d0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_006ab750();
  iVar2 = FUN_00667170();
  if (iVar2 != 0) {
    FUN_006dee50(4,"asio async_write",in_stack_0000001c);
    puVar3 = (undefined4 *)make_error_code(local_24,2);
    local_1c = *puVar3;
    local_18 = puVar3[1];
  }
  cVar1 = FUN_006caba0();
  if (cVar1 == '\0') {
    FUN_006d08b0(0x400,"handle_async_write called with null write handler");
  }
  else {
    FUN_006cadd0(&local_1c);
  }
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

