
void FUN_00738720(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a798;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x20,uVar1);
  local_8 = 0;
  iVar3 = param_2;
  FUN_00737ab0(param_2 + 0x20);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_54,uVar1,uVar2,param_2,iVar3);
  FUN_007388e0(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_00738cf0(local_54,local_54);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006f2210();
  local_8 = 0xffffffff;
  FUN_00738810();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

