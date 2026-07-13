
void __fastcall FUN_005bfa90(int param_1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  undefined4 local_28;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847838;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if ((iVar1 != 0) &&
     (iVar2 = (*(code *)**(undefined4 **)(iVar1 + 0x18))(), *(int *)(iVar2 + 0x1c) != 4)) {
    pvVar3 = operator_new(0x134);
    local_8 = 1;
    if (pvVar3 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_005c07e0(*(undefined4 *)(param_1 + 0x34),iVar1);
    }
    *(undefined4 *)(param_1 + 0x38) = local_28;
    ExceptionList = local_10;
    return;
  }
  pvVar3 = operator_new(0x134);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_005c0030(*(undefined4 *)(param_1 + 0x34),iVar1);
  }
  *(undefined4 *)(param_1 + 0x38) = local_20;
  ExceptionList = local_10;
  return;
}

