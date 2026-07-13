
void __fastcall FUN_005b49d0(int param_1)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x2c) == 0) {
    pvVar2 = operator_new(0x134);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00608580(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x2c) = local_1c;
  }
  local_8 = 0xffffffff;
  (**(code **)(**(int **)(param_1 + 0x2c) + 0x1c))(uVar1);
  ExceptionList = local_10;
  return;
}

