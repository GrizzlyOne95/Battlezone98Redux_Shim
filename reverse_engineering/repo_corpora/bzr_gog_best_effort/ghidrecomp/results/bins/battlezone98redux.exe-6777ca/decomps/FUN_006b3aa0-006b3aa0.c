
undefined4 * __thiscall FUN_006b3aa0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850719;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_006ac540(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *param_1 = uVar1;
  FUN_006ac110();
  local_8 = 0;
  pvVar2 = operator_new(0xc);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_006adfa0();
  }
  local_8._0_1_ = 0;
  FUN_00447eb0(local_1c);
  local_8._0_1_ = 2;
  uVar1 = get();
  uVar1 = FUN_006ac540(uVar1);
  param_1[8] = uVar1;
  pvVar2 = operator_new(4);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_24 = 0;
  }
  else {
    uVar1 = get();
    local_24 = FUN_006adf70(uVar1);
  }
  local_8._0_1_ = 2;
  FUN_00447eb0(local_24);
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_00447eb0(0);
  ExceptionList = local_10;
  return param_1;
}

