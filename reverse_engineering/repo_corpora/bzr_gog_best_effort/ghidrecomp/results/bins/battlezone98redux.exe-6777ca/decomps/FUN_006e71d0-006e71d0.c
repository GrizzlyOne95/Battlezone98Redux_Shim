
void FUN_006e71d0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 in_stack_0000001c;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  char *pcStack_40;
  char *pcStack_3c;
  uint uStack_38;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined1 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00854648;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_3c = (char *)0x400;
  pcStack_40 = (char *)0x6e720f;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_3c = "asio connection handle_proxy_write";
    pcStack_40 = (char *)0x400;
    uStack_44 = 0x6e722b;
    FUN_006d08b0();
  }
  pcStack_3c = "j";
  FUN_006e73d0();
  pcStack_3c = (char *)0x0;
  pcStack_40 = (char *)0x3e3;
  uStack_44 = 0x6e7245;
  FUN_006d8cc0();
  pcStack_3c = local_24;
  pcStack_40 = (char *)in_stack_0000001c;
  uStack_44 = 0x6e7252;
  cVar1 = FUN_006ab920();
  if (cVar1 == '\0') {
    pcStack_3c = local_2c;
    pcStack_40 = "\x05\\\x01";
    FUN_00421ec0();
    pcStack_40 = (char *)0x6e7277;
    FUN_00421ec0();
    pcStack_40 = (char *)0x6e727e;
    puVar2 = (undefined4 *)FUN_006d7120();
    pcStack_3c = (char *)puVar2[1];
    pcStack_40 = (char *)*puVar2;
    uStack_44 = 0x6e728a;
    cVar1 = FUN_006de530();
    if (cVar1 == '\0') {
      pcStack_3c = (char *)0x6e72c2;
      iVar3 = FUN_00667170();
      if (iVar3 != 0) {
        pcStack_3c = (char *)in_stack_0000001c;
        pcStack_40 = "asio handle_proxy_write";
        uStack_44 = 4;
        uStack_48 = 0x6e72d9;
        FUN_006dee50();
        pcStack_3c = "\x05\\\x01";
        FUN_00421ec0();
        pcStack_3c = (char *)0x6e72f0;
        FUN_00421ec0();
        pcStack_3c = (char *)0x6e72f7;
        FUN_006d70d0();
        pcStack_3c = (char *)0x3;
        pcStack_40 = local_34;
        uStack_44 = 0x6e7302;
        pcStack_3c = (char *)make_error_code();
        pcStack_40 = (char *)0x6e730e;
        FUN_006cadd0();
        local_8 = 0xffffffff;
        pcStack_3c = (char *)0x6e731d;
        std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                  ((function<void___cdecl(void)> *)&stack0x00000004);
        ExceptionList = local_10;
        return;
      }
      local_18 = auStack_50;
      local_1c = function<>(&stack0x00000004);
      FUN_006e7410();
      local_8 = 0xffffffff;
      pcStack_3c = (char *)0x6e734a;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x00000004);
      ExceptionList = local_10;
      return;
    }
  }
  pcStack_3c = "write operation aborted";
  pcStack_40 = (char *)0x1;
  uStack_44 = 0x6e72a6;
  FUN_006d47b0();
  local_8 = 0xffffffff;
  pcStack_3c = (char *)0x6e72b5;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

