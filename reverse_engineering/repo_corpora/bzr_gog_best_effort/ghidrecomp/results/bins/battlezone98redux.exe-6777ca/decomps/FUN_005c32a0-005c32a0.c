
void __fastcall FUN_005c32a0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847718;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ScavengerProcess::vftable;
  local_8 = 0;
  FUN_0069d310(param_1[0x15],uVar1);
  if (param_1[0x14] != 0) {
    FUN_005c3120();
    FUN_006a62b0(param_1[0x14],param_1[0x13]);
  }
  FUN_005c49b0();
  local_8 = 0xffffffff;
  FUN_00461630();
  ExceptionList = local_10;
  return;
}

