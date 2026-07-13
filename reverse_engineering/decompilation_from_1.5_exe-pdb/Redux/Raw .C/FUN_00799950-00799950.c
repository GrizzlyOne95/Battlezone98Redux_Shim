
void FUN_00799950(void)

{
  int iVar1;
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f628;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_007c7a20(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 == 1) {
    vector<>();
    local_8 = 0;
    local_18[0] = 1;
    FUN_0041ff90(local_18);
    local_1c = 0xe;
    FUN_0041ff90(&local_1c);
    local_20 = 0xf;
    FUN_0041ff90(&local_20);
    FUN_007c7aa0(local_2c);
    local_8 = 0xffffffff;
    FUN_0041fe20();
  }
  FUN_007c79a0();
  FUN_00740a90(0);
  ExceptionList = local_10;
  return;
}

