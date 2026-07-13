
void __thiscall FUN_006b43c0(int param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850874;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  *(int *)(param_1 + 0x334) = *(int *)(param_1 + 0x334) + 1;
  iVar2 = get(uVar1);
  if (iVar2 == 0) {
    pvVar3 = operator_new(0x4c);
    local_8._0_1_ = 1;
    if (pvVar3 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_006b3fa0();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006ca430(local_20);
  }
  uVar4 = get(uVar1);
  *param_2 = uVar4;
  local_8 = 0xffffffff;
  FUN_006c8d50();
  ExceptionList = local_10;
  return;
}

