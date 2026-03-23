
void FUN_006b45c0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008508a0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1 != 0) {
    FUN_006ca4c0(param_2);
    local_8._0_1_ = 1;
    local_8._1_3_ = 0;
    while( true ) {
      iVar2 = get(uVar1);
      if (iVar2 == 0) break;
      FUN_006c8fb0();
      FUN_006ac940(param_1,param_3,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006b40d0();
    local_8 = 0xffffffff;
    FUN_006ca540();
  }
  ExceptionList = local_10;
  return;
}

