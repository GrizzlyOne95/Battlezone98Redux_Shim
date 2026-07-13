
void FUN_006c30f0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puStack_58;
  char *pcStack_54;
  uint uStack_50;
  undefined1 *local_4c;
  undefined4 local_48;
  undefined1 local_44 [8];
  undefined4 local_3c;
  undefined1 local_38 [8];
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00851ca8;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_4c = (undefined1 *)&puStack_58;
  local_14 = uStack_50;
  local_48 = shared_ptr<>(&stack0x00000004);
  local_3c = FUN_006cbe40(local_38);
  local_8._0_1_ = 1;
  pcStack_54 = (char *)0x6c3157;
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    *(undefined1 *)(local_30 + 0x31c) = 0;
    pcStack_54 = (char *)0x6c3170;
    FUN_006ab750();
    pcStack_54 = "Pong timeout";
    puStack_58 = (undefined1 *)0x6c317d;
    basic_string<>();
    local_8._0_1_ = 2;
    pcStack_54 = local_44;
    puStack_58 = local_2c;
    uVar2 = 3000;
    FUN_00421ec0(3000);
    FUN_006dacd0(uVar2);
    local_8._0_1_ = 1;
    pcStack_54 = (char *)0x6c31a9;
    ~basic_string<>();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_54 = (char *)0x6c31b5;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  pcStack_54 = (char *)0x6c31c4;
  FUN_006c9420();
  ExceptionList = local_10;
  uStack_50 = 0x6c31d9;
  FUN_0083e885();
  return;
}

