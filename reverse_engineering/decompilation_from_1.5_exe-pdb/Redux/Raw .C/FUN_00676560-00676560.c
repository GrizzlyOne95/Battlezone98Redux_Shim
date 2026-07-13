
void FUN_00676560(int param_1,int param_2,undefined1 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = (param_2 - param_1) / 0x18;
  local_30 = iVar2 / 2;
  local_14 = uVar1;
  while (0 < local_30) {
    local_30 = local_30 + -1;
    uVar3 = FUN_00417780(local_30 * 0x18 + param_1,uVar1);
    basic_string<>(uVar3);
    local_8 = 0;
    uVar3 = FUN_00417780(local_2c,param_3);
    FUN_00676ea0(param_1,local_30,iVar2,uVar3);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

