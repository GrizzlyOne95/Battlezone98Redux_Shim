
void FUN_006b26e0(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 uVar4;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850610;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c96a0(param_1,param_2,param_3);
  uVar1 = FUN_006d93e0(param_1,param_2,uVar3);
  uVar2 = FUN_006b2540();
  if (uVar1 < uVar2) {
    uVar4 = basic_string<>("Day of month is not valid for year");
    local_8 = 0;
    uVar4 = FID_conflict_rounding_error(uVar4);
    local_8._0_1_ = 1;
    FUN_006d9460(uVar4);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006b2390();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

