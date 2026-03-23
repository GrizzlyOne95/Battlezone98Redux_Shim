
void FUN_007c3ac0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = operator_new(0x44);
  local_8 = 0;
  if (local_18 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007c3120(param_1,param_2);
  }
  local_20 = local_1c;
  local_8 = 0xffffffff;
  local_24 = local_1c;
  FUN_0041ff90(&local_24);
  iVar2 = size(uVar1);
  if (iVar2 == 1) {
    (**(code **)(**(int **)(local_14 + 0x1f0) + 0x3c))(param_1);
    FUN_007cc750();
  }
  ExceptionList = local_10;
  return;
}

