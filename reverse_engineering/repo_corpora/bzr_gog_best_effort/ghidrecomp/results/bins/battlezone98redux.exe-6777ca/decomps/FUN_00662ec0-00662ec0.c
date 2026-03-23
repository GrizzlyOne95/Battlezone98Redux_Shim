
void FUN_00662ec0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084db98;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar5 = 0;
  uVar2 = FUN_004fbb90(param_2);
  local_8 = 0;
  uVar4 = uVar2;
  uVar3 = FUN_0083fa10(param_3);
  FUN_004fbb90(uVar3);
  local_8 = 0xffffffff;
  FUN_004180b0(uVar1,uVar2,uVar4,uVar5 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

