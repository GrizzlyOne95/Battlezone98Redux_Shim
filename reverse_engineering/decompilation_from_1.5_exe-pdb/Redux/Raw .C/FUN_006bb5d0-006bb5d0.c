
void __fastcall FUN_006bb5d0(int param_1)

{
  char cVar1;
  undefined4 uStack_3c;
  undefined1 *puStack_38;
  undefined4 uStack_34;
  uint uStack_30;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008512d8;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = param_1;
  if (*(int *)(param_1 + 0x10) == 1) {
    uStack_34 = 0x6bb63b;
    cVar1 = FUN_006caba0();
    if (cVar1 != '\0') {
      uStack_34 = 0x6bb64d;
      uStack_34 = FUN_00421ec0();
      local_18 = (undefined1 *)&uStack_3c;
      local_1c = shared_ptr<>(local_14 + 0x14);
      FUN_006cabd0();
    }
    *(undefined4 *)(local_14 + 0x10) = 2;
    uStack_34 = 0x6bb682;
    uStack_34 = FUN_006ab750();
    puStack_38 = (undefined1 *)0x6bb68b;
    FUN_006cadd0();
    local_8 = 0xffffffff;
    uStack_34 = 0x6bb69a;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  else {
    uStack_34 = 3;
    puStack_38 = local_24;
    uStack_3c = 0x6bb613;
    uStack_34 = make_error_code();
    puStack_38 = (undefined1 *)0x6bb61f;
    FUN_006cadd0();
    local_8 = 0xffffffff;
    uStack_34 = 0x6bb62e;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x00000004);
  }
  ExceptionList = local_10;
  return;
}

