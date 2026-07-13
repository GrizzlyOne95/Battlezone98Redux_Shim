
undefined4 __thiscall FUN_006c6830(undefined4 param_1,undefined1 param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085238c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0066ae30(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  pvVar1 = operator_new(0xc40);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_006be3e0(param_2);
  }
  local_8._0_1_ = 0;
  uVar2 = FUN_006dc190(local_1c);
  local_8._0_1_ = 2;
  FUN_006c8b10(uVar2);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006676c0();
  uVar2 = param_1;
  get(param_1);
  FUN_006c3750(uVar2);
  ExceptionList = local_10;
  return param_1;
}

