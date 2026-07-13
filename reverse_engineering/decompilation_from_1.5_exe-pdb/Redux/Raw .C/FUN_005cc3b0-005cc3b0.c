
void FUN_005cc3b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00462630(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 != 0) {
    pvVar2 = operator_new(0x18);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))(param_2);
      local_1c = FUN_00460490(uVar3,param_2);
    }
    local_8 = 0xffffffff;
    FUN_005cc2e0(iVar1,local_1c,param_3);
  }
  ExceptionList = local_10;
  return;
}

