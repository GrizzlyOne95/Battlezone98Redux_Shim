
void FUN_00704fe0(void)

{
  undefined4 uVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  error_condition local_34 [8];
  error_condition local_2c [8];
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856e38;
  local_10 = ExceptionList;
  uVar4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d08b0(0x400,"asio con handle_async_read");
  FUN_006ab750(uVar4);
  FUN_006ff4a0(2,0);
  cVar2 = FUN_006ab920(in_stack_0000001c,local_24);
  if (cVar2 == '\0') {
    iVar6 = FUN_00667170();
    if (iVar6 != 0) {
      puVar5 = (undefined4 *)FUN_006f1850(local_44,*in_stack_0000001c,in_stack_0000001c[1]);
      local_1c = *puVar5;
      local_18 = puVar5[1];
      uVar1 = in_stack_0000001c[1];
      *(undefined4 *)(local_14 + 0x84) = *in_stack_0000001c;
      *(undefined4 *)(local_14 + 0x88) = uVar1;
      FUN_006de390(0xb);
      bVar3 = std::error_condition::operator==((error_condition *)&local_1c,local_2c);
      if (!bVar3) {
        FUN_006de390(2);
        bVar3 = std::error_condition::operator==((error_condition *)&local_1c,local_34);
        if (!bVar3) goto LAB_00705102;
      }
      FUN_006dee50(4,"asio async_read_at_least",in_stack_0000001c);
    }
  }
  else {
    puVar5 = (undefined4 *)make_error_code(local_3c,7);
    local_1c = *puVar5;
    local_18 = puVar5[1];
  }
LAB_00705102:
  cVar2 = FUN_006caba0();
  if (cVar2 == '\0') {
    FUN_006d08b0(0x400,"handle_async_read called with null read handler");
  }
  else {
    FUN_00707900(&local_1c,in_stack_00000020);
  }
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

