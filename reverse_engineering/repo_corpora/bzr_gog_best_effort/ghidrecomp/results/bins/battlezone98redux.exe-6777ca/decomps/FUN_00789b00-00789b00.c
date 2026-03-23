
void FUN_00789b00(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  char *local_3c;
  char *local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856e98;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  iVar3 = FUN_007cb0a0(uVar2);
  if (iVar3 != -1) {
    FUN_00764790(iVar3);
    FUN_00752d30(iVar3);
    local_3c = (char *)FUN_0041f870();
    local_34 = &DAT_00915540;
    puVar4 = &DAT_00915540;
    do {
      cVar1 = *local_3c;
      *local_34 = cVar1;
      local_3c = local_3c + 1;
      local_34 = local_34 + 1;
    } while (cVar1 != '\0');
    basic_string<>("instant_action");
    local_8 = 0;
    FUN_00482860(local_2c,uVar2,puVar4);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_00434170(5);
    DAT_00918328 = 0;
    FUN_007c9170(0);
    FUN_0078bb00();
    FUN_007c7930(0x17);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

