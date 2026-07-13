
void FUN_007170d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  undefined1 *local_24;
  undefined1 *local_20;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845a61;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_30 = param_1;
  uStack_34 = 0x30;
  local_14 = forward<>();
  local_8 = 0;
  if (local_14 != 0) {
    uStack_30 = param_4;
    uStack_34 = 0x71711f;
    uStack_34 = FUN_00417780();
    local_20 = (undefined1 *)&uStack_30;
    allocator<>();
    uStack_34 = param_3;
    uVar1 = FUN_00417780();
    local_24 = (undefined1 *)&uStack_34;
    FUN_00433890(uVar1);
    puVar2 = (undefined1 *)FUN_00417780(param_2);
    FUN_00722f00(*puVar2);
  }
  ExceptionList = local_10;
  return;
}

