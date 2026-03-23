
void __thiscall FUN_00612730(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047eae0(param_2);
  uVar2 = (**(code **)(*(int *)(param_1 + 0x18) + 4))(1,uVar1);
  FUN_00469900(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x110),
               *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x168),uVar2);
  uVar2 = FUN_006121c0(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xf4));
  *(undefined4 *)(param_1 + 0x240) = uVar2;
  if (*(int *)(param_1 + 0x1a0) == 0) {
    pvVar3 = operator_new(0x3c);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_004d9800(param_1);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x1a0) = local_1c;
  }
  FUN_004a77a0(0,*(undefined4 *)(param_1 + 0x240));
  FUN_00472420(0,*(undefined4 *)(param_1 + 0xf4));
  FUN_004d9950(1);
  FUN_004d9880(1);
  (**(code **)(**(int **)(param_1 + 0x240) + 0x14))(0x38d1b717);
  ExceptionList = local_10;
  return;
}

