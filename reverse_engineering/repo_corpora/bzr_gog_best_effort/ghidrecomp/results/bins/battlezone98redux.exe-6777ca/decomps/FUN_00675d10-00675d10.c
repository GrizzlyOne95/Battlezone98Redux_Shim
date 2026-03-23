
void FUN_00675d10(int param_1,int param_2,undefined1 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_34;
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ef58;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = (param_2 - param_1) / 0x1c;
  local_34 = iVar2 / 2;
  local_14 = uVar1;
  while (0 < local_34) {
    local_34 = local_34 + -1;
    uVar3 = FUN_00417780(local_34 * 0x1c + param_1,uVar1);
    FUN_00676860(uVar3);
    local_8 = 0;
    uVar3 = FUN_00417780(local_30,param_3);
    FUN_006768a0(param_1,local_34,iVar2,uVar3);
    local_8 = 0xffffffff;
    FUN_00430250();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

