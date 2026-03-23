
void FUN_00676a00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  undefined1 *local_20;
  undefined1 *local_1c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849981;
  local_10 = ExceptionList;
  uStack_28 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_2c = param_3;
  uStack_30 = 0x68;
  local_14 = forward<>();
  local_8 = 0;
  if (local_14 != 0) {
    uStack_2c = param_6;
    uStack_30 = 0x676a4c;
    uStack_30 = FUN_00417780();
    local_1c = (undefined1 *)&uStack_2c;
    allocator<>();
    uStack_30 = param_5;
    uVar1 = FUN_00417780();
    local_20 = (undefined1 *)&uStack_30;
    FUN_00433890(uVar1);
    puVar2 = (undefined1 *)FUN_00417780(param_4);
    FUN_00677180(*puVar2);
  }
  ExceptionList = local_10;
  return;
}

