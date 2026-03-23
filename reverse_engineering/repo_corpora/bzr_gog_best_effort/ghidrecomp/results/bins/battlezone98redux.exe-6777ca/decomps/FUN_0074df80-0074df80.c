
undefined4 FUN_0074df80(undefined4 param_1)

{
  undefined4 uVar1;
  uint uStack_f0;
  undefined1 local_30 [12];
  undefined4 local_24;
  int *local_1c;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085be9b;
  local_10 = ExceptionList;
  uStack_f0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_f0;
  ExceptionList = &local_10;
  local_1c = (int *)FUN_0073add0();
  local_8 = 0;
  if (local_1c != (int *)0x0) {
    local_24 = (**(code **)(*local_1c + 8))(local_30);
    FUN_0073a710(local_24);
    ExceptionList = local_10;
    return param_1;
  }
  uVar1 = FUN_0074e0d9();
  return uVar1;
}

