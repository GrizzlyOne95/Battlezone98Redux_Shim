
void FUN_0078a660(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_30 [12];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e8f8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_0081e820("Exiting Lobby because kicked by host\n",
                       DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_0081e710(uVar1);
  iVar2 = FUN_007c7a20();
  if (iVar2 == 2) {
    vector<>();
    local_8 = 0;
    local_18[0] = 1;
    FUN_0041ff90(local_18);
    local_1c = 0xe;
    FUN_0041ff90(&local_1c);
    local_20 = 0xf;
    FUN_0041ff90(&local_20);
    local_24 = 0x1f;
    FUN_0041ff90(&local_24);
    FUN_007c7aa0(local_30);
    local_8 = 0xffffffff;
    FUN_0041fe20();
  }
  FUN_007c79a0();
  FUN_007c79a0();
  uVar1 = 0;
  FUN_00764760(0);
  FUN_00740a90(uVar1);
  ExceptionList = local_10;
  return;
}

