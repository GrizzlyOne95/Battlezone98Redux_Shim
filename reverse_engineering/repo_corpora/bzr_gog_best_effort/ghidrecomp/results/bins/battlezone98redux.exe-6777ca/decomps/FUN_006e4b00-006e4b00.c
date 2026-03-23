
void FUN_006e4b00(void)

{
  char cVar1;
  undefined4 in_stack_0000001c;
  undefined1 auStack_48 [8];
  undefined4 uStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  char *pcStack_34;
  uint uStack_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
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
  pcStack_34 = (char *)0x400;
  uStack_38 = 0x6e4b3f;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_34 = "asio connection handle pre_init";
    uStack_38 = 0x400;
    iStack_3c = 0x6e4b5b;
    FUN_006d08b0();
  }
  pcStack_34 = (char *)0x6e4b69;
  cVar1 = FUN_006caba0();
  if (cVar1 != '\0') {
    iStack_3c = local_14 + 0x70;
    local_18 = (undefined1 *)&uStack_38;
    uStack_40 = 0x6e4b86;
    local_1c = shared_ptr<>();
    iStack_3c = 0x6e4b97;
    FUN_006e6250();
  }
  pcStack_34 = (char *)0x6e4b9f;
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    pcStack_34 = (char *)in_stack_0000001c;
    uStack_38 = 0x6e4bb2;
    FUN_006cadd0();
  }
  pcStack_34 = (char *)0x6e4bbd;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    local_20 = auStack_48;
    local_24 = function<>(&stack0x00000004);
    FUN_006e6560();
  }
  else {
    local_28 = auStack_48;
    local_2c = function<>(&stack0x00000004);
    FUN_006e6310();
  }
  local_8 = 0xffffffff;
  pcStack_34 = (char *)0x6e4c0d;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

