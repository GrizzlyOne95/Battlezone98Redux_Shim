
undefined4 __thiscall FUN_006675b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e304;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pvVar2 = operator_new(0x2c);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_006674f0(uVar1);
  }
  local_8 = 0xffffffff;
  FUN_0066e610(local_1c);
  local_8 = 1;
  FUN_00842710(param_1,param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

