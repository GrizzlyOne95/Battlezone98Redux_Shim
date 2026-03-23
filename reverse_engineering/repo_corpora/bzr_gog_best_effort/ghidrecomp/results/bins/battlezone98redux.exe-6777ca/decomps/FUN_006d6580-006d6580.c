
void FUN_006d6580(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000024;
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [12];
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00853570;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  iVar2 = FUN_00667170(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar2 == 0) {
    uVar3 = FUN_006ab750();
    FUN_006cadd0(uVar3);
  }
  else {
    FUN_006d8cc0(0x3e3,0);
    cVar1 = FUN_006ab920(in_stack_00000024,local_1c);
    if (cVar1 == '\0') {
      FUN_006dee50(4,"asio handle_timer",in_stack_00000024);
      uVar3 = make_error_code(local_2c,3);
      FUN_006cadd0(uVar3);
    }
    else {
      uVar3 = make_error_code(local_24,5);
      FUN_006cadd0(uVar3);
    }
  }
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x0000000c);
  ExceptionList = local_10;
  return;
}

